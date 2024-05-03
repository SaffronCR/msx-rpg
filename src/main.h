//------------------------------------------------------------------
// Star Rangers - A Dungeon Crawler for MSX2 using Fusion-C
//------------------------------------------------------------------

#ifndef MAIN_H
#define MAIN_H

#include "types.h"

//------------------------------------------------------------------
// Enums.
//------------------------------------------------------------------

enum GameState
{
	GS_NONE,
	GS_START_SCREEN,
	GS_CHARACTER_CREATION,
	GS_INTRO,
	GS_IN_GAME,
	GS_ENCOUNTER
};

//------------------------------------------------------------------
// Prototypes.
//------------------------------------------------------------------

void sr_set_display_loading(void);
void sr_set_game_state(enum GameState new_state);

#endif
