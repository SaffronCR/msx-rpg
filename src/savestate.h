//------------------------------------------------------------------
// Star Rangers - A Dungeon Crawler for MSX2 using Fusion-C
//------------------------------------------------------------------

#ifndef SAVESTATE_H
#define SAVESTATE_H

#include "character.h"
#include "main.h"

//------------------------------------------------------------------
// Defines.
//------------------------------------------------------------------

#define MAX_PARTY_SIZE 4

//------------------------------------------------------------------
// Structs.
//------------------------------------------------------------------

struct GameState
{
    struct CharacterSheet party[MAX_PARTY_SIZE];

	long int credits;

	// #TODO: Keep track of the position in the game world.
};

//------------------------------------------------------------------
// Prototypes.
//------------------------------------------------------------------

// bool sr_save_game_state(uchar *file_name, const struct GameState *state);
// bool sr_load_game_state(uchar *file_name, struct GameState *state);

#endif
