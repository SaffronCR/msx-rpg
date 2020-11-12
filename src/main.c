//------------------------------------------------------------------
// Star Rangers - A Dungeon Crawler for MSX2 using Fusion-C
//------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fusion-c/header/msx_fusion.h"

#include "types.h"
#include "system.h"
#include "combat.h"
#include "dungeon.h"
#include "menu.h"
#include "procgen.h"
#include "startscreen.h"
#include "intro.h"
#include "font.h"
#include "gfx.h"
#include "snd.h"
#include "main.h"

//------------------------------------------------------------------
// Variables.
//------------------------------------------------------------------

enum GameState game_state;

char update_frame_count = 0;

// Random seed, set to 666 for debug purposes.
uint rand_seed = 666;

//------------------------------------------------------------------
// Functions.
//------------------------------------------------------------------

void sf_set_game_state(char new_state)
{
	game_state = new_state;

	switch(game_state)
	{
		case StartScreen:	sf_set_startscreen_state();	break;
		case Intro:			sf_set_intro_state();		break;
		case Dungeon:		sf_set_dungeon_state();		break;
	}
}

void sf_update_game_state(void)
{
	// Player input must wait until the next frame is ready.
	if (sf_get_drawing_state() == Finished)
	{
		switch (game_state)
		{
			case StartScreen:	sf_update_startscreen_state();	break;
			case Intro:			sf_update_intro_state();		break;
			case Dungeon:		sf_update_dungeon_state();		break;
		}
	}
}

static char sf_interrupt(void)
{
	// Update game logic and audio in separate frames to ease the CPU load.
	update_frame_count = !update_frame_count;
	if (update_frame_count == 1)
	{
		// Update game logic.
		sf_update_game_state();
	}
	else
	{
		// Update audio.
		sf_update_snd();
	}

	// Update video.
	return sf_update_gfx();
}

void main(void)
{
	// If MSX is Turbo-R Switch CPU to Z80 Mode.
	if (ReadMSXtype() == 3)
	{
		ChangeCPU(0);
	}

	// Init random.
	srand(rand_seed);

	// Disable key sound.
	KeySound(0);

	// Clears the key buffer.
	KillKeyBuffer();

	// Initialization of the PSG (Use this function before sending data to PSG).
	// All registers will be set to 0, and stops all noises and sounds.
	InitPSG();

	// Init sound.
	sf_init_snd();

	// Set gfx configuration.
	sf_init_gfx();

	// Set interrupt.
	InitInterruptHandler();
	SetInterruptHandler(sf_interrupt);

	// Set initial game state.
	sf_set_game_state(Dungeon);

	for (;;)
	{
		// Do nothing.
	}
}
