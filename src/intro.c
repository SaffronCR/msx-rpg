//------------------------------------------------------------------
// Star Rangers - A Dungeon Crawler for MSX2 using Fusion-C
//------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fusion-c/header/msx_fusion.h"

#include "main.h"
#include "fnt.h"
#include "gfx.h"
#include "intro.h"

//------------------------------------------------------------------
// Enums.
//------------------------------------------------------------------

enum Panel
{
	FIRST,
	SECOND,
	THIRD,
	FOURTH
} current_panel;

//------------------------------------------------------------------
// Variables.
//------------------------------------------------------------------



//------------------------------------------------------------------
// Functions.
//------------------------------------------------------------------

void sr_draw_intro_text(void)
{
	// #TODO: Needs to be updated to new drawing system and actually do something.

	// // Intro text.
	// sr_set_drawing_state(Begin);
	// // Cls();
	// SetColors(0, 0, 14);

/*
	Deep in space, far away from the inhabited regions of the galaxy, lies a long-forgotten alien station.

	Since its discovery, many expeditions have tried to explore and uncover the secrets of this ancient civilization. Some with noble intentions, others seeking only personal profit.

	Neo-Midgard, as it’s known nowadays, is home to brave (or may I say foolish enough) settlers, scientists, adventurers, and bandits alike.

	Your transport ship has just arrived at Neo-Midgard's docking bay.

	You come in hopes to start anew, finding some adventures, and who knows, maybe getting rich and famous in the process.

	This is your story...
*/

	// sr_draw_text("Deep in space far away", 8*4, 8*19, 15, 14);
	// sr_draw_text("from the inhabited regions", 8*3, 8*19+9, 15, 14);
	// sr_draw_text("of the galaxy lies a long", 8*3, 8*19+9+9, 15, 14);
	// sr_draw_text("forgotten alien station", 8*3, 8*19+9+9+9, 15, 14);

	// //sr_set_drawing_state(WaitingForVDP);
	// sr_wait(1000);

	// // Go to ingame state.
	// sr_set_game_state(START_SCREEN);
}

void sr_set_intro_state(void)
{
	// #TODO: Needs to be updated to new drawing system and actually do something.
	//sr_draw_intro_text();
}

void sr_update_intro_state(void)
{
	// #TODO: Needs to be updated to new drawing system and actually do something.
}

void sr_finished_intro_drawing(void)
{
	// #TODO: Needs to be updated to new drawing system and actually do something.
}
