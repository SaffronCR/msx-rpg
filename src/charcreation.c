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

	sr_set_drawing_state(WaitingForVDP);
}

void sr_set_charcreation_state(void)
{
	sr_draw_charcreation_intro_text();
}

void sr_update_charcreation_state(void)
{
}
