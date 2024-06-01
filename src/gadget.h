//------------------------------------------------------------------
// Star Rangers - A Dungeon Crawler for MSX2 using Fusion-C
//------------------------------------------------------------------

#ifndef SAVESTATE_H
#define SAVESTATE_H

#include "main.h"
#include "character.h"

//------------------------------------------------------------------
// Defines.
//------------------------------------------------------------------

#define MAX_GADGETS 5

//------------------------------------------------------------------
// Typedefs.
//------------------------------------------------------------------

typedef struct
{
	uchar *name;
	void (*effect)(CharacterSheet *user, CharacterSheet party[], uchar party_size, CreatureSheet enemies[], uchar enemy_count);
	uchar uses;
} Gadget;

//------------------------------------------------------------------
// Prototypes.
//------------------------------------------------------------------
void sr_heal_gadget(CharacterSheet *user, CharacterSheet party[], uchar party_size, CreatureSheet enemies[], uchar enemy_count);
void sr_damage_gadget(CharacterSheet *user, CharacterSheet party[], uchar party_size, CreatureSheet enemies[], uchar enemy_count);
void sr_init_gadgets();

#endif
