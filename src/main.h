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
	NONE,
	START_SCREEN,
	CHARACTER_CREATION,
	INTRO,
	IN_GAME,
	ENCOUNTER
};

//------------------------------------------------------------------
// Variables.
//------------------------------------------------------------------

extern uchar active_page;

//------------------------------------------------------------------
// Prototypes.
//------------------------------------------------------------------

void sr_set_game_state(uchar new_state);

#endif
