//------------------------------------------------------------------
// Star Rangers - A Dungeon Crawler for MSX2 using Fusion-C
//------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fusion-c/header/msx_fusion.h"

#include "ingame.h"
#include "rnd.h"
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

uchar is_generating_dungeon_level;

//------------------------------------------------------------------
// Functions.
//------------------------------------------------------------------

bool sr_check_room_valid(uint room_x, uint room_y, uint room_size_x, uint room_size_y)
{
	// This room goes outside the map.
	if (room_x + room_size_x > LEVEL_SIZE ||
		room_y + room_size_y > LEVEL_SIZE)
	{
		return (false);
	}

	// Check if there's empty space for this room.
	for (uint x = room_x; x < room_x + room_size_x; x++)
	{
		for (uint y = room_y; y < room_y + room_size_y; y++)
		{
			if (level_map[x + y * LEVEL_SIZE] == TILE_ROOM ||
				level_map[x + y * LEVEL_SIZE] == TILE_CORRIDOR)
			{
				return (false);
			}
		}
	}

	// This room is valid.
	return (true);
}

void sr_create_corridor(uint room_x, uint room_y, uint room_size_x, uint room_size_y)
{
	uint x, y, turn_x_count, turn_y_count;

	// Connect to previous room (if there's one).
	if (prev_x != 0)
	{
		current_x = room_x + sr_random_range(0, room_size_x - 1);
		current_y = room_y + sr_random_range(0, room_size_y - 1);

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

				if (level_map[x + y * LEVEL_SIZE] == TILE_WALL)
				{
					level_map[x + y * LEVEL_SIZE] = TILE_CORRIDOR;
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

				if (level_map[x + y * LEVEL_SIZE] == TILE_WALL)
				{
					level_map[x + y * LEVEL_SIZE] = TILE_CORRIDOR;
				}
			}
		}
	}

	// Set previous coords so next room can connect to this one.
	prev_x = room_x + sr_random_range(0, room_size_x - 1);
	prev_y = room_y + sr_random_range(0, room_size_y - 1);
}

bool sr_create_room(void)
{
	uint room_x, room_y, room_size_x, room_size_y;

	room_x = sr_random_range(0, LEVEL_SIZE);
	room_y = sr_random_range(0, LEVEL_SIZE);

	room_size_x = sr_random_range(room_min_count, room_max_size);
	room_size_y = sr_random_range(room_min_size, room_max_size);

	// Check if this room is valid.
	if (sr_check_room_valid(room_x - 1, room_y - 1, room_size_x + 2, room_size_y + 2) == false)
	{
		return (false);
	}

	// Create room space.
	for (uint x = room_x; x < room_x + room_size_x; x++)
	{
		for (uint y = room_y; y < room_y + room_size_y; y++)
		{
			level_map[x + y * LEVEL_SIZE] = TILE_ROOM;
		}
	}

	// Create corridor to previous room (if exists).
	sr_create_corridor(room_x, room_y, room_size_x, room_size_y);

	return (true);
}

bool sr_is_valid_position(uint x, uint y)
{
	// Must be in a room tile.
	if (level_map[x + y * LEVEL_SIZE] != TILE_ROOM)
	{
		return (false);
	}

	// Can't be close to a corridor.
	for (uint i = x - 1; i < x + 2; i++)
	{
		for (uint j = y - 1; j < y + 2; j++)
		{
			if (i < LEVEL_SIZE && j < LEVEL_SIZE &&
				level_map[i + j * LEVEL_SIZE] == TILE_CORRIDOR)
			{
				return (false);
			}
		}
	}

	// Otherwise it's fine.
	return (true);
}

bool sr_is_generating_dungeon_level(void)
{
	return is_generating_dungeon_level;
}

bool sr_generate_dungeon_level(void)
{
	uint room_count = 0, failsafe_count = 0;
	uint stairs_x, stairs_y;

	// Set the level generator state.
	is_generating_dungeon_level = true;

	// Reset values.
	prev_x = 0;
	prev_y = 0;

	// Allocate memory for level map.
	if (level_map == NULL)
	{
		level_map = malloc(LEVEL_SIZE * LEVEL_SIZE);

		// Uh Oh...
		if (level_map == NULL)
		{
			// Set the level generator state.
			is_generating_dungeon_level = false;
			return (false);
		}
	}

	// Clear level map.
	memset(level_map, TILE_WALL, LEVEL_SIZE * LEVEL_SIZE);

	// Create rooms.
	room_count = sr_random_range(room_min_count, room_max_count);
	while (room_count > 0)
	{
		if (sr_create_room() == true)
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
				// Set the level generator state.
				is_generating_dungeon_level = false;
				return (false);
			}
		}
	}

	// Set random player position.
	do
	{
		player_pos_x = sr_random_range(1, LEVEL_SIZE);
		player_pos_y = sr_random_range(1, LEVEL_SIZE);
	} while (sr_is_valid_position(player_pos_x, player_pos_y) == false);

	// Set random stairs position.
	do
	{
		stairs_x = sr_random_range(1, LEVEL_SIZE);
		stairs_y = sr_random_range(1, LEVEL_SIZE);
	} while (sr_is_valid_position(stairs_x, stairs_y) == false ||
			 (stairs_x == player_pos_x && stairs_y == player_pos_y));

	level_map[stairs_x + stairs_y * LEVEL_SIZE] = TILE_STAIRS;

	// Set the level generator state.
	is_generating_dungeon_level = false;
	return (true);
}
