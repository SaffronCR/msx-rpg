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
#include "dungeon.h"

//------------------------------------------------------------------
// Variables.
//------------------------------------------------------------------

const sint dir_translate_x[] = {0, 1, 0, -1};
const sint dir_translate_y[] = {-1, 0, 1, 0};

uchar *dungeon_map;

uchar current_view[DUNGEON_VIEW_DX * DUNGEON_VIEW_DY];

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

void sr_draw_third_wall_far_left()
{
	sr_screen_copy(THIRD_WALL_FAR_LEFT_X, THIRD_WALL_FAR_LEFT_Y,
		THIRD_WALL_FAR_DX, THIRD_WALL_FAR_DY,
		DUNGEON_SCREEN_X,
		DUNGEON_SCREEN_Y + ((DUNGEON_SCREEN_DY - THIRD_WALL_FAR_DY) * 0.5),
		WALLS_PAGE, active_page, LOGICAL_TIMP);
}

void sr_draw_third_wall_far_right_fully()
{
	sr_screen_copy(THIRD_WALL_FAR_RIGHT_X, THIRD_WALL_FAR_RIGHT_Y,
		THIRD_WALL_FAR_DX, THIRD_WALL_FAR_DY,
		DUNGEON_SCREEN_X + DUNGEON_SCREEN_DX - THIRD_WALL_FAR_DX,
		DUNGEON_SCREEN_Y + ((DUNGEON_SCREEN_DY - THIRD_WALL_FAR_DY) * 0.5),
		WALLS_PAGE, active_page, LOGICAL_TIMP);
}

void sr_draw_third_wall_far_right_partly()
{
	sr_screen_copy(THIRD_WALL_FAR_RIGHT_X, THIRD_WALL_FAR_RIGHT_Y,
		10, THIRD_WALL_FAR_DY,
		DUNGEON_SCREEN_X + DUNGEON_SCREEN_DX - THIRD_WALL_FAR_DX,
		DUNGEON_SCREEN_Y + ((DUNGEON_SCREEN_DY - THIRD_WALL_FAR_DY) * 0.5),
		WALLS_PAGE, active_page, LOGICAL_TIMP);
}

void sr_draw_third_wall_left()
{
	sr_screen_copy(THIRD_WALL_LEFT_X, THIRD_WALL_LEFT_Y,
		THIRD_WALL_DX, THIRD_WALL_DY,
		DUNGEON_SCREEN_X + THIRD_WALL_OFFSET_X,
		DUNGEON_SCREEN_Y + ((DUNGEON_SCREEN_DY - THIRD_WALL_DY) * 0.5),
		WALLS_PAGE, active_page, LOGICAL_TIMP);
}

void sr_draw_third_wall_right()
{
	sr_screen_copy(THIRD_WALL_RIGHT_X, THIRD_WALL_RIGHT_Y,
		THIRD_WALL_DX, THIRD_WALL_DY,
		DUNGEON_SCREEN_X + DUNGEON_SCREEN_DX - THIRD_WALL_DX - THIRD_WALL_OFFSET_X,
		DUNGEON_SCREEN_Y + ((DUNGEON_SCREEN_DY - THIRD_WALL_DY) * 0.5),
		WALLS_PAGE, active_page, LOGICAL_TIMP);
}

void sr_draw_second_wall_far_left()
{
	sr_screen_copy(SECOND_WALL_FAR_LEFT_X, SECOND_WALL_FAR_LEFT_Y,
		SECOND_WALL_FAR_DX, SECOND_WALL_FAR_DY,
		DUNGEON_SCREEN_X,
		DUNGEON_SCREEN_Y + ((DUNGEON_SCREEN_DY - SECOND_WALL_FAR_DY) * 0.5),
		WALLS_PAGE, active_page, LOGICAL_TIMP);
}

void sr_draw_second_wall_far_right()
{
	sr_screen_copy(SECOND_WALL_FAR_RIGHT_X, SECOND_WALL_FAR_RIGHT_Y,
		SECOND_WALL_FAR_DX, SECOND_WALL_FAR_DY,
		DUNGEON_SCREEN_X + DUNGEON_SCREEN_DX - SECOND_WALL_FAR_DX,
		DUNGEON_SCREEN_Y + ((DUNGEON_SCREEN_DY - SECOND_WALL_FAR_DY) * 0.5),
		WALLS_PAGE, active_page, LOGICAL_TIMP);
}

void sr_draw_second_wall_left()
{
	sr_screen_copy(SECOND_WALL_LEFT_X, SECOND_WALL_LEFT_Y,
		SECOND_WALL_DX, SECOND_WALL_DY,
		DUNGEON_SCREEN_X,
		DUNGEON_SCREEN_Y + ((DUNGEON_SCREEN_DY - SECOND_WALL_DY) * 0.5),
		WALLS_PAGE, active_page, LOGICAL_TIMP);
}

void sr_draw_second_wall_right()
{
	sr_screen_copy(SECOND_WALL_RIGHT_X, SECOND_WALL_RIGHT_Y,
		SECOND_WALL_DX, SECOND_WALL_DY,
		DUNGEON_SCREEN_X + DUNGEON_SCREEN_DX - SECOND_WALL_DX,
		DUNGEON_SCREEN_Y + ((DUNGEON_SCREEN_DY - SECOND_WALL_DY) * 0.5),
		WALLS_PAGE, active_page, LOGICAL_TIMP);
}

void sr_draw_first_wall_left()
{
	sr_screen_copy(FIRST_WALL_LEFT_X, FIRST_WALL_LEFT_Y,
		FIRST_WALL_DX, FIRST_WALL_DY,
		DUNGEON_SCREEN_X, DUNGEON_SCREEN_Y,
		WALLS_PAGE, active_page, LOGICAL_TIMP);
}

void sr_draw_first_wall_right()
{
	sr_screen_copy(FIRST_WALL_RIGHT_X, FIRST_WALL_RIGHT_Y,
		FIRST_WALL_DX, FIRST_WALL_DY,
		DUNGEON_SCREEN_X + DUNGEON_SCREEN_DX - FIRST_WALL_DX, DUNGEON_SCREEN_Y,
		WALLS_PAGE, active_page, LOGICAL_TIMP);
}

void sr_draw_third_wall_front()
{
	sr_screen_copy(THIRD_FRONT_WALL_X, THIRD_FRONT_WALL_Y,
		THIRD_FRONT_WALL_DX, THIRD_FRONT_WALL_DY,
		DUNGEON_SCREEN_X + ((DUNGEON_SCREEN_DX - THIRD_FRONT_WALL_DX) * 0.5),
		DUNGEON_SCREEN_Y + ((DUNGEON_SCREEN_DY - THIRD_FRONT_WALL_DY) * 0.5),
		WALLS_PAGE, active_page, LOGICAL_IMP);
}

void sr_draw_second_wall_front()
{
	sr_screen_copy(SECOND_FRONT_WALL_X, SECOND_FRONT_WALL_Y,
		SECOND_FRONT_WALL_DX, SECOND_FRONT_WALL_DY,
		DUNGEON_SCREEN_X + ((DUNGEON_SCREEN_DX - SECOND_FRONT_WALL_DX) * 0.5),
		DUNGEON_SCREEN_Y + ((DUNGEON_SCREEN_DY - SECOND_FRONT_WALL_DY) * 0.5),
		WALLS_PAGE, active_page, LOGICAL_IMP);
}

/*
 * This is the view area:
 *
 *  x x x x x
 *  x x x x x
 *    x o x
 *
 */
void sr_update_fp_view(void)
{
	uint x, y, distx, disty;

	disty = DUNGEON_VIEW_DIST;
	for (uint iy = 0; iy < DUNGEON_VIEW_DY; iy++)
	{
		distx = DUNGEON_VIEW_DIST;
		for (uint ix = 0; ix < DUNGEON_VIEW_DX; ix++)
		{
			// Get the player's facing position.
			if (player_dir == North || player_dir == South)
			{
				x = player_pos_x + (distx * dir_translate_y[player_dir]);
				y = player_pos_y + (disty * dir_translate_y[player_dir]);
			}
			else
			{
				x = player_pos_x + (disty * dir_translate_x[player_dir]);
				y = player_pos_y - (distx * dir_translate_x[player_dir]);
			}

			// If this position is valid set the tile from the dungeon map.
			if (x < DUNGEON_SIZE && y < DUNGEON_SIZE)
			{
				current_view[ix + iy * DUNGEON_VIEW_DX] = dungeon_map[x + y * DUNGEON_SIZE];
			}
			else
			{
				// Set default state for the tile: a wall.
				current_view[ix + iy * DUNGEON_VIEW_DX] = TILE_WALL;
			}
			distx--;
		}
		disty--;
	}
}

void sr_draw_fp_view(void)
{
	// Front walls.
	if (current_view[7] == TILE_WALL)
	{
		sr_draw_second_wall_front();
	}
	else if (current_view[2] == TILE_WALL)
	{
		sr_draw_third_wall_front();
	}

	if (current_view[1 + DUNGEON_VIEW_DX * 2] == TILE_WALL)
	{
		sr_draw_first_wall_left();
	}

	if (current_view[3 + DUNGEON_VIEW_DX * 2 ] == TILE_WALL)
	{
		sr_draw_first_wall_right();
	}

	if (current_view[1 + DUNGEON_VIEW_DX] == TILE_WALL)
	{
		sr_draw_second_wall_left();
	}

	if (current_view[3 + DUNGEON_VIEW_DX] == TILE_WALL)
	{
		sr_draw_second_wall_right();
	}

	if (current_view[0 + DUNGEON_VIEW_DX] == TILE_WALL &&
		current_view[1 + DUNGEON_VIEW_DX * 2] != TILE_WALL)
	{
		sr_draw_second_wall_far_left();
	}

	if (current_view[4 + DUNGEON_VIEW_DX] == TILE_WALL &&
		current_view[1 + DUNGEON_VIEW_DX * 2] != TILE_WALL)
	{
		sr_draw_second_wall_far_right();
	}

	if (current_view[1] == TILE_WALL &&
		(current_view[7] != TILE_WALL && current_view[1 + DUNGEON_VIEW_DX * 2] != TILE_WALL))
	{
		sr_draw_third_wall_left();
	}

	if (current_view[3] == TILE_WALL &&
		(current_view[7] != TILE_WALL && current_view[3 + DUNGEON_VIEW_DX * 2 ] != TILE_WALL))
	{
		sr_draw_third_wall_right();
	}

	if (current_view[0] == TILE_WALL &&
		current_view[1 + DUNGEON_VIEW_DX * 2] != TILE_WALL)
	{
		sr_draw_third_wall_far_left();
	}

	if (current_view[4] == TILE_WALL &&
		current_view[3 + DUNGEON_VIEW_DX * 2 ] != TILE_WALL)
	{
		sr_draw_third_wall_far_right_fully();
	}
}

void sr_draw_tiles_screen_background(void)
{
	// Draw tiled background.
	for (uint x = 0; x < 11; x++)
	{
		for (uint y = 0; y < 8; y++)
		{
			sr_screen_copy(232, 188,
						   24, 24,
						   x * 24, y * 24,
						   SPRITES_PAGE, active_page, opHMMM);
		}
	}

	// Draw menu background in one solid color.
	LMMV(MENU_X, MENU_Y + active_page * SCREEN_WIDTH,
		 MENU_DX, MENU_DY,
		 0, 0);
}

void sr_draw_portraits(void)
{
	// Names.
	sr_draw_text("E.Ilba",	PORTRAIT_1_NAME_X, PORTRAIT_1_NAME_Y, 15, 0);
	sr_draw_text("Echo",	PORTRAIT_2_NAME_X, PORTRAIT_2_NAME_Y, 15, 0);
	sr_draw_text("Lisbeth",	PORTRAIT_2_NAME_X, PORTRAIT_3_NAME_Y,  6, 0);

	// Portraits.
	sr_screen_copy(PORTRAIT_SRC_X, PORTRAIT_SRC_Y,
				   PORTRAIT_SIZE, PORTRAIT_SIZE,
				   PORTRAIT_1_X, PORTRAIT_1_Y,
				   SPRITES_PAGE, active_page, opHMMM);

	sr_screen_copy(PORTRAIT_SRC_X + PORTRAIT_SIZE, PORTRAIT_SRC_Y,
				   PORTRAIT_SIZE, PORTRAIT_SIZE,
				   PORTRAIT_2_X, PORTRAIT_2_Y,
				   SPRITES_PAGE, active_page, opHMMM);

	sr_screen_copy(PORTRAIT_SRC_X + PORTRAIT_SIZE + PORTRAIT_SIZE, PORTRAIT_SRC_Y,
	 			   PORTRAIT_SIZE, PORTRAIT_SIZE,
	 			   PORTRAIT_3_X, PORTRAIT_3_Y,
	 			   SPRITES_PAGE, active_page, opHMMM);

	// HP bars.
	LMMV(HP_BAR_1_X, HP_BAR_1_Y + active_page * SCREEN_WIDTH,
		HP_BAR_SIZE_X, HP_BAR_SIZE_Y, 11, 0);
	LMMV(HP_BAR_2_X, HP_BAR_2_Y + active_page * SCREEN_WIDTH,
		HP_BAR_SIZE_X, HP_BAR_SIZE_Y, 11, 0);
	LMMV(HP_BAR_3_X, HP_BAR_3_Y + active_page * SCREEN_WIDTH,
		HP_BAR_SIZE_X, HP_BAR_SIZE_Y, 11, 0);
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

	uint menu_y = MENU_Y + MENU_Y_SPACE;
	sr_draw_text("*Attack", MENU_X, menu_y, MENU_TEXT_SELECT_COLOR, 0);

	menu_y += FONT_SIZE + MENU_Y_SPACE;
	sr_draw_text(" Streams", MENU_X, menu_y, MENU_TEXT_DEFAULT_COLOR, 0);

	menu_y += FONT_SIZE + MENU_Y_SPACE;
	sr_draw_text(" Equip", MENU_X, menu_y, MENU_TEXT_DEFAULT_COLOR, 0);

	menu_y += FONT_SIZE + MENU_Y_SPACE;
	sr_draw_text(" Flee", MENU_X, menu_y, MENU_TEXT_DEFAULT_COLOR, 0);
}

void sr_debug_draw_minimap(void)
{
	for (uint x = 0; x < DUNGEON_SIZE; x++)
	{
		for (uint y = 0; y < DUNGEON_SIZE; y++)
		{
			if (player_pos_x == x && player_pos_y == y)
			{
				// Player.
				Pset(x + 200, y + 160 + active_page * SCREEN_WIDTH, 11, 0);
			}
			else if (dungeon_map[x + y * DUNGEON_SIZE] == TILE_STAIRS)
			{
				// Stairs.
				Pset(x + 200, y + 160 + active_page * SCREEN_WIDTH, 9, 0);
			}
			else if (dungeon_map[x + y * DUNGEON_SIZE] == TILE_WALL)
			{
				// Wall.
				Pset(x + 200, y + 160 + active_page * SCREEN_WIDTH, 3, 0);
			}
			else
			{
				// Floor.
				Pset(x + 200, y + 160 + active_page * SCREEN_WIDTH, 7, 0);
			}
		}
	}
}

// Draw the current dungeon room.
void sr_draw_dungeon_screen(void)
{
	sr_set_drawing_state(Begin);

	// Screen background test.
	sr_draw_tiles_screen_background();

	// #WIP test menu.
	sr_debug_draw_test_menu();

	// Debug: Minimap.
	sr_debug_draw_minimap();

	// Debug: Palette.
	sr_debug_draw_palette();

	// Party portraits.
	sr_draw_portraits();

	// Compass.
	switch(player_dir)
	{
		case North:	sr_draw_text("N", COMPASS_X, COMPASS_Y, 9, 0);	break;
		case East:	sr_draw_text("E", COMPASS_X, COMPASS_Y, 9, 0);	break;
		case South:	sr_draw_text("S", COMPASS_X, COMPASS_Y, 9, 0);	break;
		case West:	sr_draw_text("W", COMPASS_X, COMPASS_Y, 9, 0);	break;
	}

	// #WIP: Draw a different floor in odd tiles to create ilusion of movement.
	if (player_moves == TRUE)
	{
		ceiling_tile = !ceiling_tile;
	}

	// Dungeon background.
	if (ceiling_tile == 1)
	{
		// Draw Standard background minus the floor.
		sr_screen_copy(0, 0,
			DUNGEON_SCREEN_DX, DUNGEON_SCREEN_DY - 22,
			DUNGEON_SCREEN_X, DUNGEON_SCREEN_Y,
			SPRITES_PAGE, active_page, opHMMM);

		// Draw alternate floor.
		sr_screen_copy(0, 120,
			DUNGEON_SCREEN_DX, 22,
			DUNGEON_SCREEN_X, DUNGEON_SCREEN_Y + 98,
			SPRITES_PAGE, active_page, opHMMM);
	}
	else
	{
		// Draw standard background in full.
		sr_screen_copy(0, 0,
			DUNGEON_SCREEN_DX, DUNGEON_SCREEN_DY,
			DUNGEON_SCREEN_X, DUNGEON_SCREEN_Y,
			SPRITES_PAGE, active_page, opHMMM);
	}

	// Dungeon first person view.
	sr_update_fp_view();
	sr_draw_fp_view();

	// #WIP Enemies.
	//sr_screen_copy(160,32, 55,64, 60,60, SPRITES_PAGE, active_page, LOGICAL_TIMP);
	//sr_screen_copy(169,55, 32,32, 100,110, SPRITES_PAGE, active_page, LOGICAL_TIMP);

	// #WIP test encounter RNG.
	if(sr_check_encounter() == TRUE)
	{
		sr_draw_text("ENCOUNTER!", 0, 0, 9, 0);
	}
	else
	{
		sr_draw_text("NOTHING   ", 0, 0, 5, 0);
	}

	sr_set_drawing_state(WaitingForVDP);
}

void sr_move(uint newPosX, uint newPosY)
{
	if (newPosX < DUNGEON_SIZE - 1 &&
		newPosY < DUNGEON_SIZE - 1 &&
		(dungeon_map[newPosX + newPosY * DUNGEON_SIZE] == TILE_ROOM ||
		dungeon_map[newPosX + newPosY * DUNGEON_SIZE] == TILE_CORRIDOR))
	{
		player_pos_x = newPosX;
		player_pos_y = newPosY;

		player_moves = TRUE;

		sr_encounter_step();
	}
}

void sr_rotate_left(void)
{
	if (--player_dir < North)
	{
		player_dir = West;
	}

	player_turns = TRUE;
}

void sr_rotate_right(void)
{
	if (++player_dir > West)
	{
		player_dir = North;
	}

	player_turns = TRUE;
}

// Reads input from keyboard's arrow keys and joystick port 1.
void sr_update_input_dungeon_mode(void)
{
	// Cursor.
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

	// Buttons.
	if (TriggerRead(JOY1_BUTTONB) == PRESSED ||
		TriggerRead(SPACEBAR) == PRESSED )
	{
		if (sr_is_generating_dungeon() == FALSE)
		{
			sr_generate_dungeon();
		}
	}
}

void sr_set_dungeon_state(void)
{
	// Initialize variables.
	player_moves = FALSE;
	player_turns = FALSE;
	ceiling_tile = 0;

	// Switch to 192 vertical lines (for speed gain).
	sr_set_screen_height(SH_192);

	// This may be set by the random generator in the future?
	player_dir = North;

	// Generate dungeon.
	SetColors(0,0,0);
	Cls();
	sr_draw_text("Entering the Undercity...", 8, 8, 15, 0);
	dungeon_map = NULL;
	sr_generate_dungeon();

	// Initialize encounter logic.
	sr_init_encounter();

	// Initial draw call.
	Cls();
	sr_draw_dungeon_screen();
}

void sr_update_dungeon_state(void)
{
	// Update input and dungeon view in different cycles.
	if (player_moves == FALSE && player_turns == FALSE)
	{
		sr_update_input_dungeon_mode();
	}
	else
	{
		sr_draw_dungeon_screen();

		// Reset variables.
		player_moves = FALSE;
		player_turns = FALSE;
	}
}
