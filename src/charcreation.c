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
#include "font.h"
#include "gfx.h"
#include "dungeon.h" // #WIP needed for draw portraits defines
#include "charcreation.h"

//------------------------------------------------------------------
// Functions.
//------------------------------------------------------------------

void sr_draw_portraits(void)
{
	// Names.
	sr_draw_text("E.Ilba",	PORTRAIT_1_NAME_X, PORTRAIT_1_NAME_Y, 15, 0);
	sr_draw_text("Echo",	PORTRAIT_2_NAME_X, PORTRAIT_2_NAME_Y, 15, 0);
	sr_draw_text("Lisbeth",	PORTRAIT_2_NAME_X, PORTRAIT_3_NAME_Y, 15, 0);

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

	// HP.
	sr_draw_text("22", 256-4-(8*3), PORTRAIT_1_NAME_Y+4+8, 15, 0);
	sr_draw_text("/",  256-4-(8*2), PORTRAIT_1_NAME_Y+4+8+8, 15, 0);
	sr_draw_text("25", 256-4-(8*2), PORTRAIT_1_NAME_Y+4+8+8+8, 15, 0);

	sr_draw_text("13", 256-4-(8*3), PORTRAIT_2_NAME_Y+4+8, 15, 0);
	sr_draw_text("/",  256-4-(8*2), PORTRAIT_2_NAME_Y+4+8+8, 15, 0);
	sr_draw_text("14", 256-4-(8*2), PORTRAIT_2_NAME_Y+4+8+8+8, 15, 0);

	sr_draw_text("17", 256-4-(8*3), PORTRAIT_3_NAME_Y+4+8, 15, 0);
	sr_draw_text("/",  256-4-(8*2), PORTRAIT_3_NAME_Y+4+8+8, 15, 0);
	sr_draw_text("17", 256-4-(8*2), PORTRAIT_3_NAME_Y+4+8+8+8, 15, 0);
}

void sr_draw_page_one(void)
{
	uint menu_x;
	uint menu_y;
	uint space_between_lines = 10;
	uchar normal_text_color = 10;
	uchar name_text_color = 15;
	uchar ability_text_color = 11;

	menu_x = 8;
	menu_y = 8;
	sr_draw_text("Human", menu_x, menu_y, normal_text_color, 0);
	menu_y += space_between_lines;
	sr_draw_text("Level 2", menu_x, menu_y, normal_text_color, 0);

	menu_y += space_between_lines;
	menu_y += space_between_lines;
	sr_draw_text("Might       15/+2", menu_x, menu_y, ability_text_color, 0);
	menu_y += space_between_lines;
	sr_draw_text("Dexterity   15/+2", menu_x, menu_y, ability_text_color, 0);
	menu_y += space_between_lines;
	sr_draw_text("Intellect   14/+1", menu_x, menu_y, ability_text_color, 0);
	menu_y += space_between_lines;
	sr_draw_text("Personality 13/+1", menu_x, menu_y, ability_text_color, 0);

	menu_y += space_between_lines;
	menu_y += space_between_lines;
	sr_draw_text("Attack   +2", menu_x, menu_y, normal_text_color, 0);
	menu_y += space_between_lines;
	sr_draw_text("Dodge    +0", menu_x, menu_y, normal_text_color, 0);
	menu_y += space_between_lines;
	sr_draw_text("Defense  +2", menu_x, menu_y, normal_text_color, 0);
}

void sr_draw_page_two(void)
{
	uint menu_x;
	uint menu_y;
	uint space_between_lines = 10;
	uchar normal_text_color = 10;
	uchar name_text_color = 15;
	uchar ability_text_color = 11;

	menu_x = 8;
	menu_y = 8;
	sr_draw_text("Human", menu_x, menu_y, normal_text_color, 0);
	menu_y += space_between_lines;
	sr_draw_text("Level 2", menu_x, menu_y, normal_text_color, 0);

	menu_y += space_between_lines;
	menu_y += space_between_lines;
	sr_draw_text("JOBS", menu_x, menu_y, normal_text_color, 0);
	menu_y += space_between_lines;
	sr_draw_text("Hunter     2", menu_x, menu_y, normal_text_color, 0);
	menu_y += space_between_lines;
	sr_draw_text("Pirate     1", menu_x, menu_y, normal_text_color, 0);
	menu_y += space_between_lines;
	sr_draw_text("Scientist  1", menu_x, menu_y, normal_text_color, 0);
	menu_y += space_between_lines;
	sr_draw_text("Streamer   1", menu_x, menu_y, normal_text_color, 0);
}

// #WIP this is a mockup.
void sr_draw_charcreation_intro_text(void)
{
	// Switch to 212 vertical lines.
	sr_set_screen_height(SH_212);

	sr_set_drawing_state(Begin);

	Cls();
	SetColors(0, 0, 14);

	// Portrait.
	// LMMV(8, 	8 + active_page * SCREEN_WIDTH, 34, 34, 15, 0);
	// LMMV(1+8, 1+8 + active_page * SCREEN_WIDTH, 32, 32, 3, 0);

	sr_draw_page_one();

	sr_draw_portraits();

	sr_set_drawing_state(WaitingForVDP);
}

void sr_set_charcreation_state(void)
{
	sr_draw_charcreation_intro_text();
}

void sr_update_charcreation_state(void)
{
}
