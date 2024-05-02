//------------------------------------------------------------------
// Star Rangers - A Dungeon Crawler for MSX2 using Fusion-C
//------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fusion-c/header/msx_fusion.h"

#include "createpcscr.h"
#include "encounter.h"
#include "fnt.h"
#include "gfx.h"
#include "ingame.h"
#include "intro.h"
#include "menu.h"
#include "procgen.h"
#include "rnd.h"
#include "snd.h"
#include "startscr.h"
#include "system.h"
#include "main.h"

//------------------------------------------------------------------
// Variables.
//------------------------------------------------------------------

enum GameState game_state;

uchar update_frame_count;

//------------------------------------------------------------------
// Functions.
//------------------------------------------------------------------

void sr_set_display_loading(void)
{
	sr_set_active_page(0);
	SetColors(0, 14, 0);
	Cls();
	sr_set_display_page(0);
}

void sr_set_game_state(uchar new_state)
{
	game_state = new_state;

	switch(game_state)
	{
		case GS_START_SCREEN:			sr_set_startscr_state();		break;
		case GS_CHARACTER_CREATION:		sr_set_charcreation_state();	break;
		case GS_INTRO:					sr_set_intro_state();			break;
		case GS_IN_GAME:				sr_set_ingame_state();			break;
	}
}

void sr_update_game_state(void)
{
	// Player input must wait until the next frame is ready.
	if (sr_get_drawing_state() == DS_READY)
	{
		switch (game_state)
		{
			case GS_START_SCREEN:			sr_update_startscr_state();		break;
			case GS_CHARACTER_CREATION:		sr_update_charcreation_state();	break;
			case GS_INTRO:					sr_update_intro_state();		break;
			case GS_IN_GAME:				sr_update_ingame_state();		break;
		}
	}
}

static uchar sr_interrupt(void)
{
	// Update game logic and audio in separate frames to ease the CPU load.
	update_frame_count = !update_frame_count;
	if (update_frame_count == 1)
	{
		// Update game logic.
		sr_update_game_state();
	}
	else
	{
		// Update audio.
		sr_update_snd();
	}

	// Checking game is not drawing and VDP is not busy.
	// https://www.msx.org/wiki/VDP_Status_Registers
	if (sr_get_drawing_state() == DS_END && sr_is_vdp_ready())
	{
		// Update video.
		sr_set_drawing_state(DS_READY);

		switch (game_state)
		{
			case GS_START_SCREEN:	sr_finished_startscr_drawing();	break;
			case GS_INTRO:			sr_finished_intro_drawing();	break;
			case GS_IN_GAME:		sr_finished_ingame_drawing();	break;
		}
	}

	return sr_update_gfx();
}

void main(void)
{
	// Init variables.
	update_frame_count = 0;

	// If MSX is Turbo-R Switch CPU to Z80 Mode.
	if (ReadMSXtype() == 3)
	{
		ChangeCPU(0);
	}

	// Switch VDP to 60Hz.
	VDP60Hz();

	// Reset timer.
	SetRealTimer(0);

	// Disable key sound.
	KeySound(0);

	// Clears the key buffer.
	KillKeyBuffer();

	// Initialization of the PSG (Use this function before sending data to PSG).
	// All registers will be set to 0, and stops all noises and sounds.
	InitPSG();

	// Init sound.
	sr_init_snd();

	// Set gfx configuration.
	sr_init_gfx();

	// Set interrupt.
	InitInterruptHandler();
	SetInterruptHandler(sr_interrupt);

	// Set initial game state.
	//sr_set_game_state(GS_START_SCREEN);
	sr_set_game_state(GS_IN_GAME);

	for (;;)
	{
		// Do nothing.
	}
}
