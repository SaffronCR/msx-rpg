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
#include "intro.h"

//------------------------------------------------------------------
// Functions.
//------------------------------------------------------------------

void sr_draw_intro_text(void)
{
	// Intro text.
	sr_set_drawing_state(Begin);
	// Cls();
	SetColors(0, 0, 14);

	sr_draw_text("Deep in space far away", 8*4, 8*19, 15, 14);
	sr_draw_text("from the inhabited regions", 8*3, 8*19+9, 15, 14);
	sr_draw_text("of the galaxy lies a long", 8*3, 8*19+9+9, 15, 14);
	sr_draw_text("forgotten alien station", 8*3, 8*19+9+9+9, 15, 14);

	sr_set_drawing_state(WaitingForVDP);
	sr_wait(1000);

	// Go to dungeon state.
	sr_set_game_state(StartScreen);
}

void sr_set_intro_state(void)
{
	sr_draw_intro_text();
}

void sr_update_intro_state(void)
{
}
