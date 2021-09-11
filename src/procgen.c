//------------------------------------------------------------------
// Star Rangers - A Dungeon Crawler for MSX2 using Fusion-C
//------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fusion-c/header/msx_fusion.h"
#include "fusion-c/header/vdp_sprites.h"
#include "fusion-c/header/vdp_graph2.h"

#include "main.h"
#include "dungeon.h"
#include "procgen.h"

//------------------------------------------------------------------
// Variables.
//------------------------------------------------------------------

const uint room_min_count = 4;
const uint room_max_count = 8;

const uint room_min_size = 2;
const uint room_max_size = 4;

uint prev_x;
uint prev_y;

uint current_x;
uint current_y;

uchar is_generating_dungeon;

//------------------------------------------------------------------
// Functions.
//------------------------------------------------------------------

BOOL sf_check_room_valid(uint room_x, uint room_y, uint room_size_x, uint room_size_y)
{
    // This room goes outside the map.
    if (room_x + room_size_x > DUNGEON_SIZE ||
        room_y + room_size_y > DUNGEON_SIZE)
    {
        return (FALSE);
    }

    // Check if there's empty space for this room.
    for (uint x = room_x; x < room_x + room_size_x; x++)
    {
        for (uint y = room_y; y < room_y + room_size_y; y++)
        {
            if (dungeon_map[x + y * DUNGEON_SIZE] == TILE_ROOM ||
                dungeon_map[x + y * DUNGEON_SIZE] == TILE_CORRIDOR )
            {
                return (FALSE);
            }
        }
    }

    // This room is valid.
    return (TRUE);
}

void sf_create_corridor(uint room_x, uint room_y, uint room_size_x, uint room_size_y)
{
    uint x, y, turn_x_count, turn_y_count;

    // Connect to previous room (if there's one).
    if (prev_x != 0)
    {
        current_x = room_x + rand() % room_size_x;
        current_y = room_y + rand() % room_size_y;

        x = prev_x;
        y = prev_y;

        if (abs(x - current_x) > abs(y - current_y))
        {
            turn_x_count = abs(x - current_x);
            turn_y_count = 0;
        }
        else
        {
            turn_y_count = abs(x - current_x);
            turn_x_count = 0;
        }

        while (x != current_x || y != current_y)
        {
            if (turn_x_count > 0)
            {
                turn_x_count--;
            }
            else
            {
                if (x > current_x)
                {
                    x--;
                }
                else if (x < current_x)
                {
                    x++;
                }

                if (dungeon_map[x + y * DUNGEON_SIZE] == TILE_WALL)
                {
                    dungeon_map[x + y * DUNGEON_SIZE] = TILE_CORRIDOR;
                }
            }

            if (turn_y_count > 0)
            {
                turn_y_count--;
            }
            else
            {
                if (y > current_y)
                {
                    y--;
                }
                else if (y < current_y)
                {
                    y++;
                }

                if (dungeon_map[x + y * DUNGEON_SIZE] == TILE_WALL)
                {
                    dungeon_map[x + y * DUNGEON_SIZE] = TILE_CORRIDOR;
                }
            }
        }
    }

    // Set previous coords so next room can connect to this one.
    prev_x = room_x + rand() % room_size_x;
    prev_y = room_y + rand() % room_size_y;
}

BOOL sf_create_room()
{
    uint room_x, room_y, room_size_x, room_size_y;

    room_x = rand() % DUNGEON_SIZE + 1;
    room_y = rand() % DUNGEON_SIZE + 1;

    room_size_x = rand() % (room_max_size - room_min_count + 1) + room_min_count;
    room_size_y = rand() % (room_max_size - room_min_size + 1) + room_min_size;

    // Check if this room is valid.
    if (sf_check_room_valid(room_x - 1, room_y - 1, room_size_x + 2, room_size_y + 2) == FALSE)
    {
        return (FALSE);
    }

    // Create room space.
    for (uint x = room_x; x < room_x + room_size_x; x++)
    {
        for (uint y = room_y; y < room_y + room_size_y; y++)
        {
            dungeon_map[x + y * DUNGEON_SIZE] = TILE_ROOM;
        }
    }

    // Create corridor to previous room (if exists).
    sf_create_corridor(room_x, room_y, room_size_x, room_size_y);

    return (TRUE);
}

BOOL sf_is_valid_position(uint x, uint y)
{
    // Must be in a room tile.
    if (dungeon_map[x + y * DUNGEON_SIZE] != TILE_ROOM)
    {
        return (FALSE);
    }

    // Can't be close to a corridor.
    for (uint i = x - 1; i < x + 2; i++)
    {
        for (uint j = y - 1; j < y + 2; j++)
        {
            if (i < DUNGEON_SIZE && j < DUNGEON_SIZE &&
                dungeon_map[i + j * DUNGEON_SIZE] == TILE_CORRIDOR)
            {
                return (FALSE);
            }
        }
    }

    // Otherwise it's fine.
    return (TRUE);
}

BOOL sf_is_generating_dungeon(void)
{
    return is_generating_dungeon;
}

BOOL sf_generate_dungeon(void)
{
    uint room_count = 0, failsafe_count = 0;
    uint stairs_x, stairs_y;

    // Set the dungeon generator state.
    is_generating_dungeon = TRUE;

    // Reset values.
    prev_x = 0;
    prev_y = 0;

    // Allocate memory for dungeon map.
    if (dungeon_map == NULL)
    {
        dungeon_map = malloc(DUNGEON_SIZE*DUNGEON_SIZE);

        // Uh Oh...
        if (dungeon_map == NULL)
        {
            // Set the dungeon generator state.
            is_generating_dungeon = FALSE;
            return (FALSE);
        }
    }

    // Clear dungeon map.
    memset(dungeon_map, TILE_WALL, DUNGEON_SIZE*DUNGEON_SIZE);

    // Create rooms.
    room_count = rand() % (room_max_count - room_min_count + 1) + room_min_count;
    while (room_count > 0)
    {
        if (sf_create_room() == TRUE)
        {
            room_count--;
        }
        else if (++failsafe_count > 69)
        {
            // If there's at least two rooms connected, accept this map.
            if (prev_x != 0)
            {
                room_count = 0;
            }
            else
            {
                // Set the dungeon generator state.
                is_generating_dungeon = FALSE;
                return (FALSE);
            }
        }
    }

    // Set random player position.
    do
    {
        player_pos_x = rand() % DUNGEON_SIZE + 1;
        player_pos_y = rand() % DUNGEON_SIZE + 1;
    } while (sf_is_valid_position(player_pos_x, player_pos_y) == FALSE);

    // Set random stairs position.
    do
    {
        stairs_x = rand() % DUNGEON_SIZE + 1;
        stairs_y = rand() % DUNGEON_SIZE + 1;
    } while (sf_is_valid_position(stairs_x, stairs_y) == FALSE ||
        (stairs_x == player_pos_x && stairs_y == player_pos_y));

    dungeon_map[stairs_x + stairs_y * DUNGEON_SIZE] = TILE_STAIRS;

    // Set the dungeon generator state.
    is_generating_dungeon = FALSE;
    return (TRUE);
}
