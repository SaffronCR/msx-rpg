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
	// Reset current screen.
	Cls();

	// Load the title screen.
	sr_load_sf5_image("STRTSCR.SF5", SCREEN_WIDTH * TITLE_PAGE);

	// Set active page.
	sr_set_active_page(TITLE_PAGE);

	// Begin drawing.
	sr_set_drawing_state(Begin);

	// Intro text.
	SetColors(0, 0, 14);

	sr_draw_text("PRESS SPACE KEY",		FONT_SIZE * 8, FONT_SIZE * 15, 15, 14);
	sr_draw_text("@ 2023 SAFFRON SOFT",	FONT_SIZE * 6, FONT_SIZE * 18, 15, 14);

	// Finish drawing.
	sr_set_drawing_state(End);
}

void sr_set_startscr_state(void)
{
	sr_draw_startscr_intro_text();
}

void sr_update_startscr_state(void)
{
	// TODO:
	// MENU
	// Go to load game -> ingame.
	// Go to new game -> intro.
}

void sr_finished_startscr_drawing(void)
{
	// Set display page.
	sr_set_display_page(TITLE_PAGE);
}
