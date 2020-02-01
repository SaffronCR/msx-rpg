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
#include "startscreen.h"

void sf_draw_startscreen_intro_text(void)
{
	// Intro text.
	db_state = Updating;
	// Cls();
	SetColors(0, 0, 14);

	sf_draw_text("PRESS SPACE KEY", 8*8, 8*18, 15, 14);
	sf_draw_text("@2020 SAFFRON SOFT", 8*7, 8*24, 15, 14);

	//sf_draw_text("@SAFFRON SOFT 2020", 8*6, 100, 2, 0);
	// PutText(0, 90, "********************************", LOGICAL_IMP);
/*
	sf_draw_text("<______________>", 8*6, 70,		8, 0);
	sf_draw_text("|              |", 8*6, 70+8,	8, 0);
	sf_draw_text("[______________]", 8*6, 70+8+8,	8, 0);
	sf_draw_text("SAFFRON SOFT",   8*6+8+8, 70+8,   15, 0);
*/

/*
	sf_draw_text("<_____COMMAND_____>", 8*6, 8+8,		13, 14);
	sf_draw_text("|                 |", 8*6, 8+8+8,		13, 14);
	sf_draw_text("|                 |", 8*6, 8+8+8+8,		13, 14);
	sf_draw_text("|                 |", 8*6, 8+8+8+8+8,		13, 14);
	sf_draw_text("|                 |", 8*6, 8+8+8+8+8+8,		13, 14);
	sf_draw_text("|                 |", 8*6, 8+8+8+8+8+8+8,		13, 14);
	sf_draw_text("|                 |", 8*6, 8+8+8+8+8+8+8+8,		13, 14);
	sf_draw_text("|                 |", 8*6, 8+8+8+8+8+8+8+8+8,		13, 14);
	sf_draw_text("|                 |", 8*6, 8+8+8+8+8+8+8+8+8+8,		13, 14);
	sf_draw_text("[_________________]", 8*6, 8+8+8+8+8+8+8+8+8+8+8,		13, 14);

	sf_draw_text("^TALK    SPELL", 8*6+8, 8+8+8+8,		15, 14);
	sf_draw_text("STATUS  ITEM", 8*6+8+8, 8+8+8+8+8+8,		15, 14);
	sf_draw_text("EQUIP   TACTICS", 8*6+8+8, 8+8+8+8+8+8+8+8,		15, 14);
	sf_draw_text("DOOR    SEARCH", 8*6+8+8, 8+8+8+8+8+8+8+8+8+8,		15, 14);
*/

	db_state = ReadyToSwitch;
	sf_wait(1000);

	// Go to dungeon state.
	sf_set_game_state(Intro);
}

void sf_set_startscreen_state(void)
{
	sf_draw_startscreen_intro_text();
}

void sf_update_startscreen_state(void)
{
}

