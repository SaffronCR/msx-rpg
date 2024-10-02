//------------------------------------------------------------------
// Star Rangers - A Dungeon Crawler for MSX2 using Fusion-C
//------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fusion-c/header/msx_fusion.h"

#include "fnt.h"
#include "gfx.h"
#include "menu.h"
#include "input.h"
#include "snd.h"
#include "system.h"
#include "startscr.h"

//------------------------------------------------------------------
// Menu config.
//------------------------------------------------------------------

const OptionMenu menu[] =
{
	{"Load Game", sr_load_game},
	{"New Game", sr_new_game}
};

//------------------------------------------------------------------
// Variables.
//------------------------------------------------------------------

bool is_menu_opened;

//------------------------------------------------------------------
// Functions.
//------------------------------------------------------------------

void sr_draw_start_screen(void)
{
	sr_set_loading(true);

	// Reset display.
	sr_reset_display();

	// Set active page.
	sr_set_active_page(TITLE_PAGE);

	// Load the title screen.
	sr_load_sf5_image("P0.SF5", PAGE_HEIGHT * TITLE_PAGE);

	// Begin drawing.
	sr_set_drawing_state(DS_BEGIN);

	// Intro text.
	SetColors(0, 0, 14);

	sr_draw_text("PRESS SPACE KEY",		FONT_SIZE * 8, FONT_SIZE * 16, 15, 0);
	sr_draw_text("@ 1986 SAFFRON SOFT",	FONT_SIZE * 6, FONT_SIZE * 22, 15, 0);

	// Finish drawing.
	sr_set_drawing_state(DS_END);

	sr_set_loading(false);
}

void sr_load_game(void)
{
	//#TODO: This should actually load a game, for now use it to go directly to ingame.
	sr_set_game_state(GS_IN_GAME);
}

void sr_new_game(void)
{
	sr_set_game_state(GS_INTRO);
}

void sr_open_main_menu(void)
{
	is_menu_opened = true;
	Cls();
	sr_set_current_menu(menu, 0,
		sizeof(menu) / sizeof(menu[0]),
		10, 12);
}

void sr_set_startscr_state(void)
{
	// Reset main menu state.
	is_menu_opened = false;

	// Draw start screen.
	sr_draw_start_screen();

	// Play music.
	sr_play_exploration_music();
}

void sr_update_startscr_state(void)
{
	if (is_menu_opened == true)
	{
		sr_update_current_menu();
	}
	else
	{
		if (sr_input_read_accept() == true)
		{
			sr_stop_music();

			sr_open_main_menu();
		}
	}
}

void sr_finished_startscr_drawing(void)
{
	// Set display page.
	sr_set_display_page(TITLE_PAGE);
}
