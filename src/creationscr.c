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
#include "creationscr.h"

//------------------------------------------------------------------
// Functions.
//------------------------------------------------------------------

void sr_draw_portraits(void)
{
	// Names.
	//sr_draw_text("E.Ilba",	PORTRAIT_1_NAME_X, PORTRAIT_1_NAME_Y, 15, 0);
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
}

// #WIP this is a mockup.
void sr_draw_creationscr_intro_text(void)
{
	// Switch to 212 vertical lines.
	//sr_set_screen_height(SH_212);

	sr_set_drawing_state(Begin);

	Cls();
	SetColors(0, 0, 14);

	// Portrait.
	LMMV(8, 	8 + active_page * SCREEN_WIDTH, 34, 34, 15, 0);
	LMMV(1+8, 1+8 + active_page * SCREEN_WIDTH, 32, 32, 3, 0);

	// Character sheet.
	uint menu_x = 8;
	uint menu_y = 48;
	uint space_between_lines = 10;
	uchar normal_text_color = 10;
	uchar name_text_color = 15;
	uchar ability_text_color = 11;

	// Left column.
	sr_draw_text("E.Ilba", menu_x, menu_y, name_text_color, 0);
	menu_y += space_between_lines;
	sr_draw_text("HUMAN", menu_x, menu_y, normal_text_color, 0);
	menu_y += space_between_lines;
	sr_draw_text("HUNTER", menu_x, menu_y, normal_text_color, 0);
	menu_y += space_between_lines;

	menu_y += space_between_lines;
	sr_draw_text("MIGHT        15", menu_x, menu_y, ability_text_color, 0);
	menu_y += space_between_lines;
	sr_draw_text("DEXTERITY    15", menu_x, menu_y, ability_text_color, 0);
	menu_y += space_between_lines;
	sr_draw_text("INTELLECT    14", menu_x, menu_y, ability_text_color, 0);
	menu_y += space_between_lines;
	sr_draw_text("PERSONALITY  13", menu_x, menu_y, ability_text_color, 0);

	menu_y = 160;
	sr_draw_text("HP", menu_x, menu_y, normal_text_color, 0);
	menu_y += space_between_lines;
	sr_draw_text("DODGE", menu_x, menu_y, normal_text_color, 0);
	menu_y += space_between_lines;

	// Right column.
	menu_x = 136+8;
	menu_y = 48+space_between_lines+space_between_lines+space_between_lines;
	sr_draw_text("LEVELS", menu_x, menu_y, normal_text_color, 0);
	menu_y += space_between_lines;
	sr_draw_text("HUNTER     12", menu_x, menu_y, normal_text_color, 0);
	menu_y += space_between_lines;
	sr_draw_text("SCIENTIST   3", menu_x, menu_y, normal_text_color, 0);
	menu_y += space_between_lines;
	sr_draw_text("PIRATE      1", menu_x, menu_y, normal_text_color, 0);
	menu_y += space_between_lines;
	sr_draw_text("STREAMER    1", menu_x, menu_y, normal_text_color, 0);
	menu_y += space_between_lines;

	menu_y = 160;
	sr_draw_text("ATTACK", menu_x, menu_y, normal_text_color, 0);
	menu_y += space_between_lines;
	sr_draw_text("DEFENSE", menu_x, menu_y, normal_text_color, 0);
	menu_y += space_between_lines;

	//sr_draw_portraits();

	sr_set_drawing_state(WaitingForVDP);
}

void sr_set_creationscr_state(void)
{
	sr_draw_creationscr_intro_text();
}

void sr_update_creationscr_state(void)
{
}
