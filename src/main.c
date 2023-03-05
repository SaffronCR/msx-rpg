//------------------------------------------------------------------
// Star Rangers - A Dungeon Crawler for MSX2 using Fusion-C
//------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fusion-c/header/msx_fusion.h"

#include "charcreation.h"
#include "ingame.h"
#include "encounter.h"
#include "font.h"
#include "gfx.h"
#include "intro.h"
#include "menu.h"
#include "procgen.h"
#include "snd.h"
#include "startscr.h"
#include "system.h"
#include "random.h"
#include "main.h"

//------------------------------------------------------------------
// Variables.
//------------------------------------------------------------------

enum GameState game_state;

uchar update_frame_count;

uint rand_seed;

//------------------------------------------------------------------
// Functions.
//------------------------------------------------------------------

void sr_set_game_state(uchar new_state)
{
	game_state = new_state;

	switch(game_state)
	{
		case START_SCREEN:			sr_set_startscr_state();		break;
		case CHARACTER_CREATION:	sr_set_charcreation_state();	break;
		case INTRO:					sr_set_intro_state();			break;
		case IN_GAME:				sr_set_ingame_state();			break;
	}
}

void sr_update_game_state(void)
{
	// Player input must wait until the next frame is ready.
	if (sr_get_drawing_state() == Finished)
	{
		switch (game_state)
		{
			case START_SCREEN:			sr_update_startscr_state();		break;
			case CHARACTER_CREATION:	sr_update_charcreation_state();	break;
			case INTRO:					sr_update_intro_state();		break;
			case IN_GAME:				sr_update_ingame_state();		break;
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

	// Update video.
	return sr_update_gfx();
}

void main(void)
{
	// Init variables.
	update_frame_count = 0;
	rand_seed = 666; // Random seed, set to 666 for debug purposes.

	// If MSX is Turbo-R Switch CPU to Z80 Mode.
	if (ReadMSXtype() == 3)
	{
		ChangeCPU(0);
	}

	VDP60Hz();

	// Reset timer.
	SetRealTimer(0);

	// Init random.
	sr_random_init(rand_seed);

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
	sr_set_game_state(IN_GAME);

	for (;;)
	{
		// Do nothing.
	}
}
