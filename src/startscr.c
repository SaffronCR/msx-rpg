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
#include "startscr.h"

//------------------------------------------------------------------
// Functions.
//------------------------------------------------------------------

void sr_draw_startscr_intro_text(void)
{
	// Switch to 212 vertical lines.
	sr_set_screen_height(SH_212);

	// Intro text.
	sr_set_drawing_state(Begin);
	// Cls();
	SetColors(0, 0, 14);

	sr_draw_text("PRESS SPACE KEY", 8*8, 8*18, 15, 14);
	sr_draw_text("@1987 SAFFRON SOFT", 8*7, 8*24, 15, 14);

	//sr_draw_text("@SAFFRON SOFT 2020", 8*6, 100, 2, 0);
	// PutText(0, 90, "********************************", LOGICAL_IMP);
/*
	sr_draw_text("<______________>", 8*6, 70,		8, 0);
	sr_draw_text("|              |", 8*6, 70+8,	8, 0);
	sr_draw_text("[______________]", 8*6, 70+8+8,	8, 0);
	sr_draw_text("SAFFRON SOFT",   8*6+8+8, 70+8,   15, 0);
*/

/*
	sr_draw_text("<_____COMMAND_____>", 8*6, 8+8,		13, 14);
	sr_draw_text("|                 |", 8*6, 8+8+8,		13, 14);
	sr_draw_text("|                 |", 8*6, 8+8+8+8,		13, 14);
	sr_draw_text("|                 |", 8*6, 8+8+8+8+8,		13, 14);
	sr_draw_text("|                 |", 8*6, 8+8+8+8+8+8,		13, 14);
	sr_draw_text("|                 |", 8*6, 8+8+8+8+8+8+8,		13, 14);
	sr_draw_text("|                 |", 8*6, 8+8+8+8+8+8+8+8,		13, 14);
	sr_draw_text("|                 |", 8*6, 8+8+8+8+8+8+8+8+8,		13, 14);
	sr_draw_text("|                 |", 8*6, 8+8+8+8+8+8+8+8+8+8,		13, 14);
	sr_draw_text("[_________________]", 8*6, 8+8+8+8+8+8+8+8+8+8+8,		13, 14);

	sr_draw_text("^TALK    SPELL", 8*6+8, 8+8+8+8,		15, 14);
	sr_draw_text("STATUS  ITEM", 8*6+8+8, 8+8+8+8+8+8,		15, 14);
	sr_draw_text("EQUIP   TACTICS", 8*6+8+8, 8+8+8+8+8+8+8+8,		15, 14);
	sr_draw_text("DOOR    SEARCH", 8*6+8+8, 8+8+8+8+8+8+8+8+8+8,		15, 14);
*/

	sr_set_drawing_state(WaitingForVDP);
	sr_wait(1000);

	// Go to dungeon state.
	sr_set_game_state(Intro);
}

void sr_set_startscr_state(void)
{
	sr_draw_startscr_intro_text();
}

void sr_update_startscr_state(void)
{
}

