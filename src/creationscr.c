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
#include "creationscr.h"

//------------------------------------------------------------------
// Functions.
//------------------------------------------------------------------

void sr_draw_creationscr_intro_text(void)
{
	// Switch to 212 vertical lines.
	sr_set_screen_height(SH_212);

	sr_set_drawing_state(Begin);

	Cls();
	SetColors(0, 0, 14);

	sr_draw_text("PRESS SPACE KEY", 8*8, 8*18, 15, 14);
	sr_draw_text("@1987 SAFFRON SOFT", 8*7, 8*20, 15, 14);

	sr_set_drawing_state(WaitingForVDP);
}

void sr_set_creationscr_state(void)
{
	sr_draw_creationscr_intro_text();
}

void sr_update_creationscr_state(void)
{
}
