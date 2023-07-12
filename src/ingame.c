//------------------------------------------------------------------
// Star Rangers - A Dungeon Crawler for MSX2 using Fusion-C
//------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fusion-c/header/msx_fusion.h"
#include "fusion-c/header/vdp_sprites.h"
#include "fusion-c/header/vdp_graph2.h"

#include "procgen.h"
#include "gfx.h"
#include "encounter.h"
#include "ingame.h"

//------------------------------------------------------------------
// Variables.
//------------------------------------------------------------------

const sint dir_translate_x[] = {0, 1, 0, -1};
const sint dir_translate_y[] = {-1, 0, 1, 0};

uchar *level_map;

uchar current_view[LEVEL_VIEW_DX * LEVEL_VIEW_DY];

uchar player_moves;
uchar player_turns;

uchar ceiling_tile;

uint player_pos_x;
uint player_pos_y;

enum Direction player_dir;

uchar joy;

//------------------------------------------------------------------
// Functions.
//------------------------------------------------------------------

void sr_draw_third_wall_far_left(uint offset_left, uint offset_right)
{
	sr_page_copy(THIRD_WALL_FAR_LEFT_X + offset_left, THIRD_WALL_FAR_LEFT_Y,
		THIRD_WALL_FAR_DX - offset_left - offset_right, THIRD_WALL_FAR_DY,
		offset_left,
		(LEVEL_SCREEN_DY - THIRD_WALL_FAR_DY) * 0.5,
		WALLS_PAGE, BACKBUFFER_PAGE, LOGICAL_TIMP);
}

void sr_draw_third_wall_far_right(uint offset_left, uint offset_right)
{
	sr_page_copy(THIRD_WALL_FAR_RIGHT_X + offset_left, THIRD_WALL_FAR_RIGHT_Y,
		THIRD_WALL_FAR_DX - offset_left - offset_right, THIRD_WALL_FAR_DY,
		LEVEL_SCREEN_DX - THIRD_WALL_FAR_DX + offset_left,
		(LEVEL_SCREEN_DY - THIRD_WALL_FAR_DY) * 0.5,
		WALLS_PAGE, BACKBUFFER_PAGE, LOGICAL_TIMP);
}

void sr_draw_third_wall_left(uint offset_left, uint offset_right)
{
	sr_page_copy(THIRD_WALL_LEFT_X + offset_left, THIRD_WALL_LEFT_Y,
		THIRD_WALL_DX - offset_left - offset_right, THIRD_WALL_DY,
		THIRD_WALL_OFFSET_X + offset_left,
		(LEVEL_SCREEN_DY - THIRD_WALL_DY) * 0.5,
		WALLS_PAGE, BACKBUFFER_PAGE, LOGICAL_TIMP);
}

void sr_draw_third_wall_right(uint offset_left, uint offset_right)
{
	sr_page_copy(THIRD_WALL_RIGHT_X + offset_left, THIRD_WALL_RIGHT_Y,
		THIRD_WALL_DX - offset_left - offset_right, THIRD_WALL_DY,
		LEVEL_SCREEN_DX - THIRD_WALL_DX - THIRD_WALL_OFFSET_X + offset_left,
		(LEVEL_SCREEN_DY - THIRD_WALL_DY) * 0.5,
		WALLS_PAGE, BACKBUFFER_PAGE, LOGICAL_TIMP);
}

void sr_draw_second_wall_far_left(void)
{
	sr_page_copy(SECOND_WALL_FAR_LEFT_X, SECOND_WALL_FAR_LEFT_Y,
		SECOND_WALL_FAR_DX, SECOND_WALL_FAR_DY,
		0,
		(LEVEL_SCREEN_DY - SECOND_WALL_FAR_DY) * 0.5,
		WALLS_PAGE, BACKBUFFER_PAGE, LOGICAL_TIMP);
}

void sr_draw_second_wall_far_right(void)
{
	sr_page_copy(SECOND_WALL_FAR_RIGHT_X, SECOND_WALL_FAR_RIGHT_Y,
		SECOND_WALL_FAR_DX, SECOND_WALL_FAR_DY,
		LEVEL_SCREEN_DX - SECOND_WALL_FAR_DX,
		(LEVEL_SCREEN_DY - SECOND_WALL_FAR_DY) * 0.5,
		WALLS_PAGE, BACKBUFFER_PAGE, LOGICAL_TIMP);
}

void sr_draw_second_wall_left(uint offset_left, uint offset_right)
{
	sr_page_copy(SECOND_WALL_LEFT_X + offset_left, SECOND_WALL_LEFT_Y,
		SECOND_WALL_DX - offset_left - offset_right, SECOND_WALL_DY,
		offset_left,
		(LEVEL_SCREEN_DY - SECOND_WALL_DY) * 0.5,
		WALLS_PAGE, BACKBUFFER_PAGE, LOGICAL_TIMP);
}

void sr_draw_second_wall_right(uint offset_left, uint offset_right)
{
	sr_page_copy(SECOND_WALL_RIGHT_X + offset_left, SECOND_WALL_RIGHT_Y,
		SECOND_WALL_DX - offset_left - offset_right, SECOND_WALL_DY,
		LEVEL_SCREEN_DX - SECOND_WALL_DX + offset_left,
		(LEVEL_SCREEN_DY - SECOND_WALL_DY) * 0.5,
		WALLS_PAGE, BACKBUFFER_PAGE, LOGICAL_TIMP);
}

void sr_draw_first_wall_left(void)
{
	sr_page_copy(FIRST_WALL_LEFT_X, FIRST_WALL_LEFT_Y,
		FIRST_WALL_DX, FIRST_WALL_DY,
		0, 0,
		WALLS_PAGE, BACKBUFFER_PAGE, LOGICAL_TIMP);
}

void sr_draw_first_wall_right(void)
{
	sr_page_copy(FIRST_WALL_RIGHT_X, FIRST_WALL_RIGHT_Y,
		FIRST_WALL_DX, FIRST_WALL_DY,
		LEVEL_SCREEN_DX - FIRST_WALL_DX, 0,
		WALLS_PAGE, BACKBUFFER_PAGE, LOGICAL_TIMP);
}

void sr_draw_third_wall_front(void)
{
	sr_page_copy(THIRD_FRONT_WALL_X, THIRD_FRONT_WALL_Y,
		THIRD_FRONT_WALL_DX, THIRD_FRONT_WALL_DY,
		(LEVEL_SCREEN_DX - THIRD_FRONT_WALL_DX) * 0.5,
		(LEVEL_SCREEN_DY - THIRD_FRONT_WALL_DY) * 0.5,
		WALLS_PAGE, BACKBUFFER_PAGE, LOGICAL_IMP);
}

void sr_draw_second_wall_front(void)
{
	sr_page_copy(SECOND_FRONT_WALL_X, SECOND_FRONT_WALL_Y,
		SECOND_FRONT_WALL_DX, SECOND_FRONT_WALL_DY,
		(LEVEL_SCREEN_DX - SECOND_FRONT_WALL_DX) * 0.5,
		(LEVEL_SCREEN_DY - SECOND_FRONT_WALL_DY) * 0.5,
		WALLS_PAGE, BACKBUFFER_PAGE, LOGICAL_IMP);
}

//  This is the view area:
//   x x x x x
//   x x x x x
//     x o x

void sr_update_fp_view(void)
{
	uint x, y, distx, disty;

	disty = LEVEL_VIEW_DIST;
	for (uint iy = 0; iy < LEVEL_VIEW_DY; iy++)
	{
		distx = LEVEL_VIEW_DIST;
		for (uint ix = 0; ix < LEVEL_VIEW_DX; ix++)
		{
			// Get the player's facing position.
			if (player_dir == NORTH || player_dir == SOUTH)
			{
				x = player_pos_x + (distx * dir_translate_y[player_dir]);
				y = player_pos_y + (disty * dir_translate_y[player_dir]);
			}
			else
			{
				x = player_pos_x + (disty * dir_translate_x[player_dir]);
				y = player_pos_y - (distx * dir_translate_x[player_dir]);
			}

			// If this position is valid set the tile from the level map.
			if (x < LEVEL_SIZE && y < LEVEL_SIZE)
			{
				current_view[ix + iy * LEVEL_VIEW_DX] = level_map[x + y * LEVEL_SIZE];
			}
			else
			{
				// Set default state for the tile: a wall.
				current_view[ix + iy * LEVEL_VIEW_DX] = TILE_WALL;
			}
			distx--;
		}
		disty--;
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
	return (current_view[1 + LEVEL_VIEW_DX * 2] == TILE_WALL);
}

bool sr_is_second_wall_left(void)
{
	return (current_view[1 + LEVEL_VIEW_DX] == TILE_WALL);
}

bool sr_is_third_wall_left(void)
{
	return (current_view[1] == TILE_WALL);
}

bool sr_is_second_wall_far_left(void)
{
	return (current_view[0 + LEVEL_VIEW_DX] == TILE_WALL);
}

bool sr_is_third_wall_far_left(void)
{
	return (current_view[0] == TILE_WALL);
}

bool sr_is_first_wall_right(void)
{
	return (current_view[3 + LEVEL_VIEW_DX * 2] == TILE_WALL);
}

bool sr_is_second_wall_right(void)
{
	return (current_view[3 + LEVEL_VIEW_DX] == TILE_WALL);
}

bool sr_is_third_wall_right(void)
{
	return (current_view[3] == TILE_WALL);
}

bool sr_is_second_wall_far_right(void)
{
	return (current_view[4 + LEVEL_VIEW_DX] == TILE_WALL);
}

bool sr_is_third_wall_far_right(void)
{
	return (current_view[4] == TILE_WALL);
}

void sr_draw_fp_view(void)
{
	// Background.

	if (ceiling_tile == 1)
	{
		// Draw Standard background minus the floor.
		sr_page_copy(0, 0,
			LEVEL_SCREEN_DX, LEVEL_SCREEN_DY - 22,
			0, 0,
			SPRITES_PAGE, BACKBUFFER_PAGE, opHMMM);

		// Draw alternate floor.
		sr_page_copy(0, 120,
			LEVEL_SCREEN_DX, 22,
			0, 98,
			SPRITES_PAGE, BACKBUFFER_PAGE, opHMMM);
	}
	else
	{
		// Draw standard background in full.
		sr_page_copy(0, 0,
			LEVEL_SCREEN_DX, LEVEL_SCREEN_DY,
			0, 0,
			SPRITES_PAGE, BACKBUFFER_PAGE, opHMMM);
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
			sr_page_copy(232, 188,
						   24, 24,
						   x * 24, y * 24,
						   SPRITES_PAGE, sr_get_active_page(), opHMMM);
		}
	}

	// Draw menu background in one solid color.
	LMMV(MENU_X, MENU_Y + sr_get_active_page() * SCREEN_WIDTH,
		 MENU_DX, MENU_DY,
		 0, 0);
}

void sr_draw_portraits(void)
{
	// Names.
	sr_draw_text("E.Ilba",	PORTRAIT_1_NAME_X, PORTRAIT_1_NAME_Y, 15, 0);
	sr_draw_text("Lisbeth",	PORTRAIT_2_NAME_X, PORTRAIT_2_NAME_Y, 15, 0);
	sr_draw_text("Krevar",	PORTRAIT_3_NAME_X, PORTRAIT_3_NAME_Y, 15, 0);
	sr_draw_text("Echo",	PORTRAIT_4_NAME_X, PORTRAIT_4_NAME_Y, 15, 0);

	// Portraits.
	sr_page_copy(PORTRAIT_SRC_X, PORTRAIT_SRC_Y,
				   PORTRAIT_SIZE, PORTRAIT_SIZE,
				   PORTRAIT_1_X, PORTRAIT_1_Y,
				   SPRITES_PAGE, sr_get_active_page(), opHMMM);

	sr_page_copy(PORTRAIT_SRC_X, PORTRAIT_SRC_Y + PORTRAIT_SIZE,
				   PORTRAIT_SIZE, PORTRAIT_SIZE,
				   PORTRAIT_2_X, PORTRAIT_2_Y,
				   SPRITES_PAGE, sr_get_active_page(), opHMMM);

	sr_page_copy(PORTRAIT_SRC_X, PORTRAIT_SRC_Y + PORTRAIT_SIZE + PORTRAIT_SIZE,
	 			   PORTRAIT_SIZE, PORTRAIT_SIZE,
	 			   PORTRAIT_3_X, PORTRAIT_3_Y,
	 			   SPRITES_PAGE, sr_get_active_page(), opHMMM);

	sr_page_copy(PORTRAIT_SRC_X, PORTRAIT_SRC_Y + PORTRAIT_SIZE + PORTRAIT_SIZE + PORTRAIT_SIZE,
	 			   PORTRAIT_SIZE, PORTRAIT_SIZE,
	 			   PORTRAIT_4_X, PORTRAIT_4_Y,
	 			   SPRITES_PAGE, sr_get_active_page(), opHMMM);

	// HP text.
	sr_draw_text("10/12", 	PORTRAIT_1_NAME_X + PORTRAIT_SIZE + 1, PORTRAIT_1_NAME_Y + 8, 15, 0);
	sr_draw_text("8/8", 	PORTRAIT_2_NAME_X + PORTRAIT_SIZE + 1, PORTRAIT_2_NAME_Y + 8, 15, 0);
	sr_draw_text("7/7", 	PORTRAIT_3_NAME_X + PORTRAIT_SIZE + 1, PORTRAIT_3_NAME_Y + 8, 15, 0);
	sr_draw_text("9/9",		PORTRAIT_4_NAME_X + PORTRAIT_SIZE + 1, PORTRAIT_4_NAME_Y + 8, 15, 0);

	// // HP bars.
	// LMMV(HP_BAR_1_X, HP_BAR_1_Y + get_active_page() * SCREEN_WIDTH,
	// 	HP_BAR_SIZE_X, HP_BAR_SIZE_Y, 11, 0);
	// LMMV(HP_BAR_2_X, HP_BAR_2_Y + get_active_page() * SCREEN_WIDTH,
	// 	HP_BAR_SIZE_X, HP_BAR_SIZE_Y, 11, 0);
	// LMMV(HP_BAR_3_X, HP_BAR_3_Y + get_active_page() * SCREEN_WIDTH,
	// 	HP_BAR_SIZE_X, HP_BAR_SIZE_Y, 11, 0);
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
	sr_draw_text("E.Ilba", MENU_X, menu_y, MENU_TEXT_DEFAULT_COLOR, 0);

	menu_y += FONT_SIZE + MENU_Y_SPACE;

	menu_y += FONT_SIZE + MENU_Y_SPACE;
	sr_draw_text("~Attack", MENU_X, menu_y, MENU_TEXT_SELECT_COLOR, 0);

	menu_y += FONT_SIZE + MENU_Y_SPACE;
	sr_draw_text(" Gadget", MENU_X, menu_y, MENU_TEXT_DEFAULT_COLOR, 0);

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

	// #SPRITE #WIP
	PutSprite(0, 0, MENU_X-8, menu_y, 0);
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
				Pset(x + 20, y + 160 + sr_get_active_page() * SCREEN_WIDTH, 11, 0);
			}
			else if (level_map[x + y * LEVEL_SIZE] == TILE_STAIRS)
			{
				// Stairs.
				Pset(x + 20, y + 160 + sr_get_active_page() * SCREEN_WIDTH, 9, 0);
			}
			else if (level_map[x + y * LEVEL_SIZE] == TILE_WALL)
			{
				// Wall.
				Pset(x + 20, y + 160 + sr_get_active_page() * SCREEN_WIDTH, 3, 0);
			}
			else
			{
				// Floor.
				Pset(x + 20, y + 160 + sr_get_active_page() * SCREEN_WIDTH, 7, 0);
			}
		}
	}
}

// Draw the current level room.
void sr_draw_level_screen(void)
{
	sr_set_drawing_state(Begin);

	// #WIP Screen background test.
	//sr_draw_tiles_screen_background();

	// #WIP Test menu.
	//sr_debug_draw_test_menu();

	// Debug: Minimap.
	//sr_debug_draw_minimap();

	// Debug: Palette.
	//sr_debug_draw_palette();

	// Party portraits.
	sr_draw_portraits();

	// Compass.
	switch(player_dir)
	{
		case NORTH:	sr_draw_text("N", COMPASS_X, COMPASS_Y, 9, 0);	break;
		case EAST:	sr_draw_text("E", COMPASS_X, COMPASS_Y, 9, 0);	break;
		case SOUTH:	sr_draw_text("S", COMPASS_X, COMPASS_Y, 9, 0);	break;
		case WEST:	sr_draw_text("W", COMPASS_X, COMPASS_Y, 9, 0);	break;
	}

	// #WIP Draw a different floor in odd tiles to create ilusion of movement.
	if (player_moves == true)
	{
		ceiling_tile = !ceiling_tile;
	}

	// Dungeon first person view.
	sr_update_fp_view();
	sr_draw_fp_view();

	// #WIP Enemies.
	//sr_page_copy(175,192, 50,60, 30,60, SPRITES_PAGE, get_active_page(), LOGICAL_TIMP);

	// sr_page_copy(224,224, 32,32, 50,80, SPRITES_PAGE, get_active_page(), LOGICAL_TIMP);
	// sr_page_copy(224,192, 32,32, 90,80, SPRITES_PAGE, get_active_page(), LOGICAL_TIMP);

	// // hit frame test.
	// sr_page_copy(224,224, 32,32, 50,80, SPRITES_PAGE, get_active_page(), LOGICAL_TNOT);
	// sr_page_copy(224,192, 32,32, 90,80, SPRITES_PAGE, get_active_page(), LOGICAL_TNOT);

	// // #WIP Test encounter RNG.
	// if(sr_check_encounter() == true)
	// {
	// 	sr_draw_text("ENCOUNTER!", 0, 0, 9, 0);
	// }
	// else
	// {
	// 	sr_draw_text("NOTHING   ", 0, 0, 5, 0);
	// }

	sr_set_drawing_state(End);
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

		player_moves = true;

		sr_encounter_step();
	}
}

void sr_rotate_left(void)
{
	if (--player_dir < NORTH)
	{
		player_dir = WEST;
	}

	player_turns = true;
}

void sr_rotate_right(void)
{
	if (++player_dir > WEST)
	{
		player_dir = NORTH;
	}

	player_turns = true;
}

// Reads input from keyboard's arrow keys and joystick port 1.
void sr_update_input_level_mode(void)
{
	// Movement.
	for (uchar i = 0; i < 2; i++)
	{
		joy = JoystickRead(i);

		switch (joy)
		{
			case UP:
				sr_move(player_pos_x + dir_translate_x[player_dir],
						player_pos_y + dir_translate_y[player_dir]);
				break;

			case DOWN:
				sr_move(player_pos_x - dir_translate_x[player_dir],
						player_pos_y - dir_translate_y[player_dir]);
				break;

			case LEFT:
				sr_rotate_left();
				break;

			case RIGHT:
				sr_rotate_right();
				break;
		}
	}

	// Actions.
	if (TriggerRead(JOY1_BUTTONB) == PRESSED ||
		TriggerRead(SPACEBAR) == PRESSED )
	{
		if (sr_is_generating_dungeon_level() == false)
		{
			sr_generate_dungeon_level();
		}
	}
}

void sr_set_ingame_state(void)
{
	// Initialize variables.
	player_moves = false;
	player_turns = false;
	ceiling_tile = 0;

	// This may be set by the random generator in the future?
	player_dir = NORTH;

	// Generate level.
	SetColors(0,0,0);
	Cls();
	sr_draw_text("Entering the Undercity...", 8, 8, 15, 0);
	level_map = NULL;
	sr_generate_dungeon_level();

	// Initialize encounter logic.
	sr_init_encounter();

	// Initial draw call.
	Cls();
	sr_draw_level_screen();
}

void sr_update_ingame_state(void)
{
	// Update input and level view in different cycles.
	if (player_moves == false && player_turns == false)
	{
		sr_update_input_level_mode();
	}
	else
	{
		sr_draw_level_screen();

		// Reset variables.
		player_moves = false;
		player_turns = false;
	}
}

void sr_finished_ingame_drawing(void)
{
	// Copy finished drawing of the first person view from back to front.
	sr_page_copy(0, 0,
		LEVEL_SCREEN_DX, LEVEL_SCREEN_DY,
		LEVEL_SCREEN_X, LEVEL_SCREEN_Y,
		BACKBUFFER_PAGE, sr_get_active_page(), opHMMM);
}
