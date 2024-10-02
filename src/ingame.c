//------------------------------------------------------------------
// Star Rangers - A Dungeon Crawler for MSX2 using Fusion-C
//------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fusion-c/header/msx_fusion.h"

#include "procgen.h"
#include "gfx.h"
#include "snd.h"
#include "encounter.h"
#include "input.h"
#include "system.h"
#include "ingame.h"

//------------------------------------------------------------------
// Variables.
//------------------------------------------------------------------

const sint dir_translate_x[] = {0, 1, 0, -1};
const sint dir_translate_y[] = {-1, 0, 1, 0};

uchar *level_map;

uchar current_view[LEVEL_VIEW_SIZE_X * LEVEL_VIEW_SIZE_Y];

uchar player_moved;
uchar player_turned;

bool is_underground;
uchar floor_tile;

uint player_pos_x;
uint player_pos_y;

enum Direction player_dir;
enum Direction compass_dir;

bool update_portraits;

//------------------------------------------------------------------
// Functions.
//------------------------------------------------------------------

void sr_draw_third_wall_far_left(uint offset_left, uint offset_right)
{
	sr_page_copy_trans(THIRD_WALL_FAR_LEFT_X + offset_left, THIRD_WALL_FAR_LEFT_Y,
		THIRD_WALL_FAR_SIZE_X - offset_left - offset_right, THIRD_WALL_FAR_SIZE_Y,
		LEVEL_SCREEN_X + offset_left,
		(LEVEL_SCREEN_SIZE_Y - THIRD_WALL_FAR_SIZE_Y) * 0.5,
		WALLS_PAGE, BACKBUFFER_PAGE);
}

void sr_draw_third_wall_far_right(uint offset_left, uint offset_right)
{
	sr_page_copy_trans(THIRD_WALL_FAR_RIGHT_X + offset_left, THIRD_WALL_FAR_RIGHT_Y,
		THIRD_WALL_FAR_SIZE_X - offset_left - offset_right, THIRD_WALL_FAR_SIZE_Y,
		LEVEL_SCREEN_X + LEVEL_SCREEN_SIZE_X - THIRD_WALL_FAR_SIZE_X + offset_left,
		(LEVEL_SCREEN_SIZE_Y - THIRD_WALL_FAR_SIZE_Y) * 0.5,
		WALLS_PAGE, BACKBUFFER_PAGE);
}

void sr_draw_third_wall_left(uint offset_left, uint offset_right)
{
	sr_page_copy_trans(THIRD_WALL_LEFT_X + offset_left, THIRD_WALL_LEFT_Y,
		THIRD_WALL_SIZE_X - offset_left - offset_right, THIRD_WALL_SIZE_Y,
		LEVEL_SCREEN_X + THIRD_WALL_OFFSET_X + offset_left,
		(LEVEL_SCREEN_SIZE_Y - THIRD_WALL_SIZE_Y) * 0.5,
		WALLS_PAGE, BACKBUFFER_PAGE);
}

void sr_draw_third_wall_right(uint offset_left, uint offset_right)
{
	sr_page_copy_trans(THIRD_WALL_RIGHT_X + offset_left, THIRD_WALL_RIGHT_Y,
		THIRD_WALL_SIZE_X - offset_left - offset_right, THIRD_WALL_SIZE_Y,
		LEVEL_SCREEN_X + LEVEL_SCREEN_SIZE_X - THIRD_WALL_SIZE_X - THIRD_WALL_OFFSET_X + offset_left,
		(LEVEL_SCREEN_SIZE_Y - THIRD_WALL_SIZE_Y) * 0.5,
		WALLS_PAGE, BACKBUFFER_PAGE);
}

void sr_draw_second_wall_far_left(void)
{
	sr_page_copy_trans(SECOND_WALL_FAR_LEFT_X, SECOND_WALL_FAR_LEFT_Y,
		SECOND_WALL_FAR_SIZE_X, SECOND_WALL_FAR_SIZE_Y,
		LEVEL_SCREEN_X,
		(LEVEL_SCREEN_SIZE_Y - SECOND_WALL_FAR_SIZE_Y) * 0.5,
		WALLS_PAGE, BACKBUFFER_PAGE);
}

void sr_draw_second_wall_far_right(void)
{
	sr_page_copy_trans(SECOND_WALL_FAR_RIGHT_X, SECOND_WALL_FAR_RIGHT_Y,
		SECOND_WALL_FAR_SIZE_X, SECOND_WALL_FAR_SIZE_Y,
		LEVEL_SCREEN_X + LEVEL_SCREEN_SIZE_X - SECOND_WALL_FAR_SIZE_X,
		(LEVEL_SCREEN_SIZE_Y - SECOND_WALL_FAR_SIZE_Y) * 0.5,
		WALLS_PAGE, BACKBUFFER_PAGE);
}

void sr_draw_second_wall_left(uint offset_left, uint offset_right)
{
	sr_page_copy_trans(SECOND_WALL_LEFT_X + offset_left, SECOND_WALL_LEFT_Y,
		SECOND_WALL_SIZE_X - offset_left - offset_right, SECOND_WALL_SIZE_Y,
		LEVEL_SCREEN_X + offset_left,
		(LEVEL_SCREEN_SIZE_Y - SECOND_WALL_SIZE_Y) * 0.5,
		WALLS_PAGE, BACKBUFFER_PAGE);
}

void sr_draw_second_wall_right(uint offset_left, uint offset_right)
{
	sr_page_copy_trans(SECOND_WALL_RIGHT_X + offset_left, SECOND_WALL_RIGHT_Y,
		SECOND_WALL_SIZE_X - offset_left - offset_right, SECOND_WALL_SIZE_Y,
		LEVEL_SCREEN_X + LEVEL_SCREEN_SIZE_X - SECOND_WALL_SIZE_X + offset_left,
		(LEVEL_SCREEN_SIZE_Y - SECOND_WALL_SIZE_Y) * 0.5,
		WALLS_PAGE, BACKBUFFER_PAGE);
}

void sr_draw_first_wall_left(void)
{
	sr_page_copy_trans(FIRST_WALL_LEFT_X, FIRST_WALL_LEFT_Y,
		FIRST_WALL_SIZE_X, FIRST_WALL_SIZE_Y,
		LEVEL_SCREEN_X, 0,
		WALLS_PAGE, BACKBUFFER_PAGE);
}

void sr_draw_first_wall_right(void)
{
	sr_page_copy_trans(FIRST_WALL_RIGHT_X, FIRST_WALL_RIGHT_Y,
		FIRST_WALL_SIZE_X, FIRST_WALL_SIZE_Y,
		LEVEL_SCREEN_X + LEVEL_SCREEN_SIZE_X - FIRST_WALL_SIZE_X, 0,
		WALLS_PAGE, BACKBUFFER_PAGE);
}

void sr_draw_third_wall_front(void)
{
	sr_page_copy(THIRD_FRONT_WALL_X, THIRD_FRONT_WALL_Y,
		THIRD_FRONT_WALL_SIZE_X, THIRD_FRONT_WALL_SIZE_Y,
		LEVEL_SCREEN_X + (LEVEL_SCREEN_SIZE_X - THIRD_FRONT_WALL_SIZE_X) * 0.5,
		(LEVEL_SCREEN_SIZE_Y - THIRD_FRONT_WALL_SIZE_Y) * 0.5,
		WALLS_PAGE, BACKBUFFER_PAGE);
}

void sr_draw_second_wall_front(void)
{
	sr_page_copy(SECOND_FRONT_WALL_X, SECOND_FRONT_WALL_Y,
		SECOND_FRONT_WALL_SIZE_X, SECOND_FRONT_WALL_SIZE_Y,
		LEVEL_SCREEN_X + (LEVEL_SCREEN_SIZE_X - SECOND_FRONT_WALL_SIZE_X) * 0.5,
		(LEVEL_SCREEN_SIZE_Y - SECOND_FRONT_WALL_SIZE_Y) * 0.5,
		WALLS_PAGE, BACKBUFFER_PAGE);
}

//  This is the view area:
//   x x x x x
//   x x x x x
//     x o x

void sr_update_fp_view(void)
{
	uint x, y, dist_x, dist_y;

	dist_y = LEVEL_VIEW_DIST;
	for (uint iy = 0; iy < LEVEL_VIEW_SIZE_Y; iy++)
	{
		dist_x = LEVEL_VIEW_DIST;
		for (uint ix = 0; ix < LEVEL_VIEW_SIZE_X; ix++)
		{
			// Get the player's facing position.
			if (player_dir == DIR_NORTH || player_dir == DIR_SOUTH)
			{
				x = player_pos_x + (dist_x * dir_translate_y[player_dir]);
				y = player_pos_y + (dist_y * dir_translate_y[player_dir]);
			}
			else
			{
				x = player_pos_x + (dist_y * dir_translate_x[player_dir]);
				y = player_pos_y - (dist_x * dir_translate_x[player_dir]);
			}

			// If this position is valid set the tile from the level map.
			if (x < LEVEL_SIZE && y < LEVEL_SIZE)
			{
				current_view[ix + iy * LEVEL_VIEW_SIZE_X] = level_map[x + y * LEVEL_SIZE];
			}
			else
			{
				// Set default state for the tile: a wall.
				current_view[ix + iy * LEVEL_VIEW_SIZE_X] = TILE_WALL;
			}
			dist_x--;
		}
		dist_y--;
	}
}

bool sr_is_second_wall_front(void)
{
	return (current_view[7] == TILE_WALL);
}

bool sr_is_third_wall_front(void)
{
	return (current_view[2] == TILE_WALL);
}

bool sr_is_first_wall_left(void)
{
	return (current_view[1 + LEVEL_VIEW_SIZE_X * 2] == TILE_WALL);
}

bool sr_is_second_wall_left(void)
{
	return (current_view[1 + LEVEL_VIEW_SIZE_X] == TILE_WALL);
}

bool sr_is_third_wall_left(void)
{
	return (current_view[1] == TILE_WALL);
}

bool sr_is_second_wall_far_left(void)
{
	return (current_view[0 + LEVEL_VIEW_SIZE_X] == TILE_WALL);
}

bool sr_is_third_wall_far_left(void)
{
	return (current_view[0] == TILE_WALL);
}

bool sr_is_first_wall_right(void)
{
	return (current_view[3 + LEVEL_VIEW_SIZE_X * 2] == TILE_WALL);
}

bool sr_is_second_wall_right(void)
{
	return (current_view[3 + LEVEL_VIEW_SIZE_X] == TILE_WALL);
}

bool sr_is_third_wall_right(void)
{
	return (current_view[3] == TILE_WALL);
}

bool sr_is_second_wall_far_right(void)
{
	return (current_view[4 + LEVEL_VIEW_SIZE_X] == TILE_WALL);
}

bool sr_is_third_wall_far_right(void)
{
	return (current_view[4] == TILE_WALL);
}

void sr_draw_fp_view(void)
{
	// Background.

	// sr_draw_rectangle(BG_FRONT_X, BACKBUFFER_PAGE*PAGE_HEIGHT,
	// 	 LEVEL_SCREEN_SIZE_X, LEVEL_SCREEN_SIZE_Y,
	// 	 BG_FRONT_COLOR);

	// Front is just a black rectangle.
	sr_draw_rectangle(BG_FRONT_X, BG_FRONT_Y,
		 BG_FRONT_SIZE_X, BG_FRONT_SIZE_Y,
		 BG_FRONT_COLOR);

	// Ceiling.
	if (is_underground == true)
	{
		// Draw underground ceiling.
		sr_page_copy_fast(BG_UNDERGROUND_CEILING_X, BG_UNDERGROUND_CEILING_Y,
			BG_UNDERGROUND_CEILING_SIZE_X, BG_UNDERGROUND_CEILING_SIZE_Y,
			LEVEL_SCREEN_X, 0,
			IMAGES_PAGE, BACKBUFFER_PAGE);
	}
	else
	{
		// Draw surface ceiling.
		sr_page_copy_fast(BG_SURFACE_CEILING_X, BG_SURFACE_CEILING_Y,
			BG_SURFACE_CEILING_SIZE_X, BG_SURFACE_CEILING_SIZE_Y,
			LEVEL_SCREEN_X, 0,
			IMAGES_PAGE, BACKBUFFER_PAGE);
	}

	// Floor.
	if (floor_tile == 0)
	{
		// Draw entire standard floor.
		sr_page_copy_fast(BG_FLOOR_X, BG_FLOOR_Y,
			BG_FLOOR_SIZE_X, BG_FLOOR_SIZE_Y,
			BG_FLOOR_DST_X, BG_FLOOR_DST_Y,
			IMAGES_PAGE, BACKBUFFER_PAGE);
	}
	else
	{
		// Draw partial standard floor.
		sr_page_copy_fast(BG_FLOOR_X, BG_FLOOR_Y,
			BG_FLOOR_SIZE_X, BG_ALT_FLOOR_SIZE_Y_1,
			BG_FLOOR_DST_X, BG_ALT_FLOOR_DST_Y_1,
			IMAGES_PAGE, BACKBUFFER_PAGE);

		// Draw alternate floor.
		sr_page_copy_fast(BG_ALT_FLOOR_X, BG_ALT_FLOOR_Y,
			BG_FLOOR_SIZE_X, BG_ALT_FLOOR_SIZE_Y_2,
			BG_FLOOR_DST_X, BG_ALT_FLOOR_DST_Y_2,
			IMAGES_PAGE, BACKBUFFER_PAGE);
	}

	// Front walls.

	if (sr_is_second_wall_front())
	{
		sr_draw_second_wall_front();
	}
	else if (sr_is_third_wall_front())
	{
		sr_draw_third_wall_front();
	}

	// Left walls.

	if (sr_is_first_wall_left())
	{
		sr_draw_first_wall_left();
	}

	if (sr_is_second_wall_left())
	{
		if (sr_is_second_wall_front() &&
			sr_is_first_wall_left())
		{
			// Fully occluded.
		}
		else if (sr_is_second_wall_front())
		{
			sr_draw_second_wall_left(0, 17);
		}
		else if (sr_is_first_wall_left())
		{
			sr_draw_second_wall_left(42, 0);
		}
		else
		{
			sr_draw_second_wall_left(0, 0);
		}
	}

	if (sr_is_third_wall_left())
	{
		if (sr_is_second_wall_front() &&
			(sr_is_first_wall_left() ||
			sr_is_second_wall_left()))
		{
			// Fully occluded.
		}
		else if (sr_is_third_wall_front() &&
			sr_is_second_wall_left())
		{
			// Fully occluded.
		}
		else if (sr_is_first_wall_left() &&
			sr_is_second_wall_left() == false)
		{
			if (sr_is_third_wall_front())
			{
				sr_draw_third_wall_left(30, 6);
			}
			else
			{
				sr_draw_third_wall_left(30, 0);
			}
		}
		else if (sr_is_second_wall_front())
		{
			sr_draw_third_wall_left(0, 22);
		}
		else if (sr_is_third_wall_front())
		{
			sr_draw_third_wall_left(0, 6);
		}
		else if (sr_is_second_wall_left())
		{
			sr_draw_third_wall_left(45, 0);
		}
		else
		{
			sr_draw_third_wall_left(0, 0);
		}
	}

	if (sr_is_second_wall_far_left())
	{
		if (sr_is_first_wall_left() ||
			sr_is_second_wall_left())
		{
			// Fully occluded.
		}
		else
		{
			sr_draw_second_wall_far_left();
		}
	}

	if (sr_is_third_wall_far_left())
	{
		if (sr_is_first_wall_left() ||
			sr_is_second_wall_left())
		{
			// Fully occluded.
		}
		else if (sr_is_third_wall_left())
		{
			if (sr_is_second_wall_far_left())
			{
				// Fully occluded.
			}
			else
			{
				sr_draw_third_wall_far_left(0, 16);
			}
		}
		else if (sr_is_second_wall_far_left())
		{
			sr_draw_third_wall_far_left(13, 0);
		}
		else
		{
			sr_draw_third_wall_far_left(0, 0);
		}
	}

	// Right walls.

	if (sr_is_first_wall_right())
	{
		sr_draw_first_wall_right();
	}

	if (sr_is_second_wall_right())
	{
		if (sr_is_second_wall_front() &&
			sr_is_first_wall_right())
		{
			// Fully occluded.
		}
		else if (sr_is_second_wall_front())
		{
			sr_draw_second_wall_right(17, 0);
		}
		else if (sr_is_first_wall_right())
		{
			sr_draw_second_wall_right(0, 42);
		}
		else
		{
			sr_draw_second_wall_right(0, 0);
		}
	}

	if (sr_is_third_wall_right())
	{
		if (sr_is_second_wall_front() &&
			(sr_is_first_wall_right() ||
			sr_is_second_wall_right()))
		{
			// Fully occluded.
		}
		else if (sr_is_third_wall_front() &&
			sr_is_second_wall_right())
		{
			// Fully occluded.
		}
		else if (sr_is_first_wall_right() &&
			sr_is_second_wall_right() == false)
		{
			if (sr_is_third_wall_front())
			{
				sr_draw_third_wall_right(6, 30);
			}
			else
			{
				sr_draw_third_wall_right(0, 30);
			}
		}
		else if (sr_is_second_wall_front())
		{
			sr_draw_third_wall_right(22, 0);
		}
		else if (sr_is_third_wall_front())
		{
			sr_draw_third_wall_right(6, 0);
		}
		else if (sr_is_second_wall_right())
		{
			sr_draw_third_wall_right(0, 45);
		}
		else
		{
			sr_draw_third_wall_right(0, 0);
		}
	}

	if (sr_is_second_wall_far_right())
	{
		if (sr_is_first_wall_right() ||
			sr_is_second_wall_right())
		{
			// Fully occluded.
		}
		else
		{
			sr_draw_second_wall_far_right();
		}
	}

	if (sr_is_third_wall_far_right())
	{
		if (sr_is_first_wall_right() ||
			sr_is_second_wall_right())
		{
			// Fully occluded.
		}
		else if (sr_is_third_wall_right())
		{
			if (sr_is_second_wall_far_right())
			{
				// Fully occluded.
			}
			else
			{
				sr_draw_third_wall_far_right(16, 0);
			}
		}
		else if (sr_is_second_wall_far_right())
		{
			sr_draw_third_wall_far_right(0, 13);
		}
		else
		{
			sr_draw_third_wall_far_right(0, 0);
		}
	}
}

void sr_draw_tiles_screen_background(void)
{
	// Draw tiled background.
	for (uint x = 0; x < 11; x++)
	{
		for (uint y = 0; y < 8; y++)
		{
			sr_page_copy_fast(232, 188,
						   24, 24,
						   x * 24, y * 24,
						   IMAGES_PAGE, sr_get_active_page());
		}
	}

	// Draw menu background in one solid color.
	sr_draw_rectangle(MENU_SIZE_X, MENU_Y + sr_get_active_page() * PAGE_HEIGHT,
		 MENU_SIZE_X, MENU_SIZE_Y,
		 0);
}

void sr_draw_portraits(void)
{
	sr_set_drawing_state(DS_BEGIN);

	// Names.
	sr_draw_text("E.Ilba",	PORTRAIT_1_NAME_X, PORTRAIT_1_NAME_Y, PORTRAIT_NAME_COLOR, 0);
	sr_draw_text("Lisbeth",	PORTRAIT_2_NAME_X, PORTRAIT_2_NAME_Y, PORTRAIT_NAME_COLOR, 0);
	sr_draw_text("Krevar",	PORTRAIT_3_NAME_X, PORTRAIT_3_NAME_Y, PORTRAIT_NAME_COLOR, 0);
	sr_draw_text("Echo",	PORTRAIT_4_NAME_X, PORTRAIT_4_NAME_Y, PORTRAIT_NAME_COLOR, 0);

	// Portraits.
	sr_page_copy_fast(PORTRAIT_SRC_X, PORTRAIT_SRC_Y,
				   PORTRAIT_SIZE, PORTRAIT_SIZE,
				   PORTRAIT_1_X, PORTRAIT_1_Y,
				   IMAGES_PAGE, sr_get_active_page());

	sr_page_copy_fast(PORTRAIT_SRC_X, PORTRAIT_SRC_Y + PORTRAIT_SIZE,
				   PORTRAIT_SIZE, PORTRAIT_SIZE,
				   PORTRAIT_2_X, PORTRAIT_2_Y,
				   IMAGES_PAGE, sr_get_active_page());

	sr_page_copy_fast(PORTRAIT_SRC_X, PORTRAIT_SRC_Y + PORTRAIT_SIZE + PORTRAIT_SIZE,
	 			   PORTRAIT_SIZE, PORTRAIT_SIZE,
	 			   PORTRAIT_3_X, PORTRAIT_3_Y,
	 			   IMAGES_PAGE, sr_get_active_page());

	sr_page_copy_fast(PORTRAIT_SRC_X, PORTRAIT_SRC_Y + PORTRAIT_SIZE + PORTRAIT_SIZE + PORTRAIT_SIZE,
	 			   PORTRAIT_SIZE, PORTRAIT_SIZE,
	 			   PORTRAIT_4_X, PORTRAIT_4_Y,
	 			   IMAGES_PAGE, sr_get_active_page());

	// HP text.
	sr_draw_text("10/12", 	PORTRAIT_1_NAME_X + PORTRAIT_SIZE + 1, PORTRAIT_1_NAME_Y + 8, PORTRAIT_NAME_COLOR, 0);
	sr_draw_text("8/8", 	PORTRAIT_2_NAME_X + PORTRAIT_SIZE + 1, PORTRAIT_2_NAME_Y + 8, PORTRAIT_NAME_COLOR, 0);
	sr_draw_text("7/7", 	PORTRAIT_3_NAME_X + PORTRAIT_SIZE + 1, PORTRAIT_3_NAME_Y + 8, PORTRAIT_NAME_COLOR, 0);
	sr_draw_text("9/9",		PORTRAIT_4_NAME_X + PORTRAIT_SIZE + 1, PORTRAIT_4_NAME_Y + 8, PORTRAIT_NAME_COLOR, 0);

	// // HP bars.
	// LMMV(HP_BAR_1_X, HP_BAR_1_Y + get_active_page() * SCREEN_HEIGHT,
	// 	HP_BAR_SIZE_X, HP_BAR_SIZE_Y, 11, 0);
	// LMMV(HP_BAR_2_X, HP_BAR_2_Y + get_active_page() * SCREEN_HEIGHT,
	// 	HP_BAR_SIZE_X, HP_BAR_SIZE_Y, 11, 0);
	// LMMV(HP_BAR_3_X, HP_BAR_3_Y + get_active_page() * SCREEN_HEIGHT,
	// 	HP_BAR_SIZE_X, HP_BAR_SIZE_Y, 11, 0);

	sr_set_drawing_state(DS_END);
}

void sr_debug_draw_test_menu(void)
{
	// #WIP

	//"Menu"
	//"Attack"
	//"Gadgets"
	//"Streams"
	//"Flee"
	//"Move"
	//"Search"
	//"Party"
	//"System"
	//"Back"

/**************************************************************************/
// Initial combat encounter

	// uint menu_y = MENU_Y + MENU_Y_SPACE;
	// sr_draw_text("~Attack", MENU_X, menu_y, MENU_TEXT_SELECT_COLOR, 0);

	// menu_y += FONT_SIZE + MENU_Y_SPACE;
	// sr_draw_text(" Talk", MENU_X, menu_y, MENU_TEXT_DEFAULT_COLOR, 0);

	// menu_y += FONT_SIZE + MENU_Y_SPACE;
	// sr_draw_text(" Flee", MENU_X, menu_y, MENU_TEXT_DEFAULT_COLOR, 0);
/**************************************************************************/
// Attack

	uint menu_y = MENU_Y + MENU_Y_SPACE;
	sr_draw_text("E.Ilba", MENU_SIZE_X, menu_y, MENU_TEXT_DEFAULT_COLOR, 0);

	menu_y += FONT_SIZE + MENU_Y_SPACE;

	menu_y += FONT_SIZE + MENU_Y_SPACE;
	sr_draw_text("~Attack", MENU_SIZE_X, menu_y, MENU_TEXT_SELECT_COLOR, 0);

	menu_y += FONT_SIZE + MENU_Y_SPACE;
	sr_draw_text(" Gadget", MENU_SIZE_X, menu_y, MENU_TEXT_DEFAULT_COLOR, 0);

/**************************************************************************/
// Talk

	// uint menu_y = MENU_Y + MENU_Y_SPACE;
	// sr_draw_text("Slime wants", MENU_X, menu_y, MENU_TEXT_DEFAULT_COLOR, 0);
	// menu_y += FONT_SIZE + MENU_Y_SPACE;
	// sr_draw_text("health potion", MENU_X, menu_y, MENU_TEXT_DEFAULT_COLOR, 0);

	// menu_y += FONT_SIZE + MENU_Y_SPACE;

	// menu_y += FONT_SIZE + MENU_Y_SPACE;
	// sr_draw_text("~Give item", MENU_X, menu_y, MENU_TEXT_SELECT_COLOR, 0);

	// menu_y += FONT_SIZE + MENU_Y_SPACE;
	// sr_draw_text(" Refuse", MENU_X, menu_y, MENU_TEXT_DEFAULT_COLOR, 0);
/**************************************************************************/
}

void sr_debug_draw_minimap(void)
{
	for (uint x = 0; x < LEVEL_SIZE; x++)
	{
		for (uint y = 0; y < LEVEL_SIZE; y++)
		{
			if (player_pos_x == x && player_pos_y == y)
			{
				// Player.
				sr_draw_pixel(x + 20, y + 160 + sr_get_active_page() * PAGE_HEIGHT, 11);
			}
			else if (level_map[x + y * LEVEL_SIZE] == TILE_STAIRS)
			{
				// Stairs.
				sr_draw_pixel(x + 20, y + 160 + sr_get_active_page() * PAGE_HEIGHT, 9);
			}
			else if (level_map[x + y * LEVEL_SIZE] == TILE_WALL)
			{
				// Wall.
				sr_draw_pixel(x + 20, y + 160 + sr_get_active_page() * PAGE_HEIGHT, 3);
			}
			else
			{
				// Floor.
				sr_draw_pixel(x + 20, y + 160 + sr_get_active_page() * PAGE_HEIGHT, 7);
			}
		}
	}
}

// Draw the current level room.
void sr_draw_level_screen(void)
{
	sr_set_drawing_state(DS_BEGIN);

	// Update compass.
	if (compass_dir != player_dir)
	{
		compass_dir = player_dir;

		switch(compass_dir)
		{
			case DIR_NORTH:	sr_draw_text("N", COMPASS_X, COMPASS_Y, COMPASS_COLOR, 0);	break;
			case DIR_EAST:	sr_draw_text("E", COMPASS_X, COMPASS_Y, COMPASS_COLOR, 0);	break;
			case DIR_SOUTH:	sr_draw_text("S", COMPASS_X, COMPASS_Y, COMPASS_COLOR, 0);	break;
			case DIR_WEST:	sr_draw_text("W", COMPASS_X, COMPASS_Y, COMPASS_COLOR, 0);	break;
		}
	}

	// #WIP Draw a different floor in odd tiles to create ilusion of movement.
	if (player_moved == true)
	{
		floor_tile = !floor_tile;
	}

	// Level first person view.
	sr_update_fp_view();
	sr_draw_fp_view();

	sr_set_drawing_state(DS_END);
}

void sr_move(uint new_pos_x, uint new_pos_y)
{
	if (new_pos_x < LEVEL_SIZE - 1 &&
		new_pos_y < LEVEL_SIZE - 1 &&
		(level_map[new_pos_x + new_pos_y * LEVEL_SIZE] == TILE_ROOM ||
		level_map[new_pos_x + new_pos_y * LEVEL_SIZE] == TILE_CORRIDOR))
	{
		player_pos_x = new_pos_x;
		player_pos_y = new_pos_y;

		player_moved = true;

		sr_encounter_step();
	}
}

void sr_rotate_left(void)
{
	if (player_dir == DIR_NORTH)
	{
		player_dir = DIR_WEST;
	}
	else
	{
		player_dir--;
	}

	player_turned = true;
}

void sr_rotate_right(void)
{
	if (player_dir == DIR_WEST)
	{
		player_dir = DIR_NORTH;
	}
	else
	{
		player_dir++;
	}

	player_turned = true;
}

void sr_update_input_level_mode(void)
{
	// Movement.
	switch (sr_input_read_dpad_continuous())
	{
		case DPAD_UP:
			sr_move(player_pos_x + dir_translate_x[player_dir],
					player_pos_y + dir_translate_y[player_dir]);
			break;

		case DPAD_DOWN:
			sr_move(player_pos_x - dir_translate_x[player_dir],
					player_pos_y - dir_translate_y[player_dir]);
			break;

		case DPAD_LEFT:
			sr_rotate_left();
			break;

		case DPAD_RIGHT:
			sr_rotate_right();
			break;
	}

	// Actions.
	if (sr_debug_input_read_regen_dungeon() == true)
	{
		if (sr_is_generating_dungeon_level() == false)
		{
			sr_generate_dungeon_level();
		}
	}
}

void sr_set_ingame_state(void)
{
	sr_set_loading(true);

	// Initialize variables.
	player_moved = false;
	player_turned = false;
	floor_tile = 0;
	is_underground = false;
	update_portraits = false;

	// This may be set by the random generator in the future?
	player_dir = DIR_NORTH;
	compass_dir = DIR_NONE;

	// Set loading.
	sr_reset_display();

	// Load images.
	sr_load_sf5_image("P1.SF5", PAGE_HEIGHT * BACKBUFFER_PAGE);
	sr_load_sf5_image("P3.SF5", PAGE_HEIGHT * WALLS_PAGE);

	// Initialize drawing state and pages.
	sr_set_drawing_state(DS_READY);
	sr_set_active_page(0);
	sr_set_display_page(0);

	// Generate level.
	SetColors(0,0,0);
	Cls();
	sr_draw_text("Entering the Undercity...", 8, 8, 15, 0);
	level_map = NULL;
	sr_generate_dungeon_level();

	// Initialize encounter logic.
	sr_init_encounter();

	// Initial draw calls.
	Cls();
	sr_draw_level_screen();
	sr_draw_portraits();

	sr_set_loading(false);

	// Play music.
	sr_play_exploration_music();
}

void sr_update_ingame_state(void)
{
	if (update_portraits == true)
	{
		update_portraits = false;

		sr_draw_portraits();
	}
	else if (player_moved == false && player_turned == false)
	{
		sr_update_input_level_mode();
	}
	else
	{
		sr_draw_level_screen();

		// Reset variables.
		player_moved = false;
		player_turned = false;
	}
}

void sr_finished_ingame_drawing(void)
{
	// Copy finished drawing of the first person view from back to front.
	sr_page_copy_y_fast(LEVEL_SCREEN_X + LEVEL_SCREEN_SIZE_X, PAGE_HEIGHT, LEVEL_SCREEN_Y, LEVEL_SCREEN_SIZE_Y, 1);
}
