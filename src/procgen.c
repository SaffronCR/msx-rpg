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

int room_min_count = 6;
int room_max_count = 12;

int room_min_size = 2;
int room_max_size = 3;

int prev_x = 0;
int prev_y = 0;

int current_x = 0;
int current_y = 0;

char sf_check_room_valid(int room_x, int room_y, int room_size_x, int room_size_y)
{
    // This room goes outside the map.
    if (room_x < 0 ||
        room_y < 0 ||
        room_x + room_size_x > DUNGEON_SIZE ||
        room_y + room_size_y > DUNGEON_SIZE)
    {
        return (FALSE);
    }

    // Check if there's empty space for this room.
    for (int x = room_x; x < room_x + room_size_x; x++)
    {
        for (int y = room_y; y < room_y + room_size_y; y++)
        {
            if (dungeon_map[x + y * DUNGEON_SIZE] == TILE_ROOM)
            {
                return (FALSE);
            }
        }
    }

    // This room is valid.
    return (TRUE);
}

void sf_create_corridor(int room_x, int room_y, int room_size_x, int room_size_y)
{
    int x, y, turn_x_count, turn_y_count;

    // Connect to previous room (if there's one).
    if (prev_x != 0)
    {
        current_x = room_x + rand() % room_size_x;
        current_y = room_y + rand() % room_size_y;

        x = prev_x;
        y = prev_y;

        if( abs(x - current_x) > abs(y - current_y))
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

char sf_create_room()
{
    int room_x, room_y, room_size_x, room_size_y;

    room_x = rand() % DUNGEON_SIZE;
    room_y = rand() % DUNGEON_SIZE;

    room_size_x = rand() % (room_max_size + 1);

    if (room_size_x < room_min_size)
    {
        room_size_x = room_min_size;
    }

    room_size_y = rand() % (room_max_size + 1);

    if (room_size_y < room_min_size)
    {
        room_size_y = room_min_size;
    }

    // Check if this room is valid.
    if (sf_check_room_valid(room_x - 1, room_y - 1, room_size_x + 2, room_size_y + 2) == FALSE)
    {
        return (FALSE);
    }

    // Create room space.
    for (int x = room_x; x < room_x + room_size_x; x++)
    {
        for (int y = room_y; y < room_y + room_size_y; y++)
        {
            dungeon_map[x + y * DUNGEON_SIZE] = TILE_ROOM;
        }
    }

    sf_create_corridor(room_x, room_y, room_size_x, room_size_y);

    return (TRUE);
}

char sf_generate_dungeon(void)
{
    uint failsafe_count = 0;

    // Random room count;
    int room_count = rand() % (room_max_count + 1);

    if (room_count < room_min_count)
    {
        room_count = room_min_count;
    }

    // Allocate memory for dungeon map.
    if (dungeon_map == NULL)
    {
        dungeon_map = malloc(DUNGEON_SIZE*DUNGEON_SIZE);

        if (dungeon_map == NULL)
        {
            // Uh Oh...
            return (FALSE);
        }
    }

    // Clear dungeon map.
    memset(dungeon_map, TILE_WALL, DUNGEON_SIZE*DUNGEON_SIZE);

    // Create rooms.
    while (room_count > 0)
    {
        if (sf_create_room() == TRUE)
        {
            room_count--;
        }
        else if (++failsafe_count > 200)
        {
            // Clear dungeon map.
            memset(dungeon_map, TILE_ROOM, DUNGEON_SIZE*DUNGEON_SIZE);

            return (FALSE);
        }
    }

    // Set random player position.
    do
    {
        player_pos_x = rand() % DUNGEON_SIZE;
        player_pos_y = rand() % DUNGEON_SIZE;
    } while (dungeon_map[player_pos_x + player_pos_y * DUNGEON_SIZE] != TILE_ROOM);

    return (TRUE);
}
