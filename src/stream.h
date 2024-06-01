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

#define MAX_STREAMS 5

//------------------------------------------------------------------
// Typedefs.
//------------------------------------------------------------------

typedef struct
{
	uchar *name;
	void (*effect)(CharacterSheet *streamer, CharacterSheet party[], uchar party_size, CreatureSheet enemies[], uchar enemy_count);
	uchar cooldown;
	uchar current_cooldown;
} Stream;

//------------------------------------------------------------------
// Prototypes.
//------------------------------------------------------------------
void sr_boost_signal(CharacterSheet *streamer, CharacterSheet party[], uchar party_size, CreatureSheet enemies[], uchar enemy_count);
void sr_distract_signal(CharacterSheet *streamer, CharacterSheet party[], uchar party_size, CreatureSheet enemies[], uchar enemy_count);
void sr_init_streams();

#endif
