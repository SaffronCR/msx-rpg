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
	None,
	StartScreen,
	CharacterCreation,
    Intro,
	HubCity,
	Encounter,
	InGame,
	Camp,
	CharacterSheet,
	Shop
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
