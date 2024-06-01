//------------------------------------------------------------------
// Star Rangers - A Dungeon Crawler for MSX2 using Fusion-C
//------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gadget.h"

//------------------------------------------------------------------
// Variables.
//------------------------------------------------------------------

Gadget gadgets[MAX_GADGETS];

//------------------------------------------------------------------
// Functions.
//------------------------------------------------------------------

void sr_heal_gadget(CharacterSheet *user, CharacterSheet party[], uchar party_size, CreatureSheet enemies[], uchar enemy_count)
{
	uint heal_amount = 10 + user->base_stats.intellect;
	for (int i = 0; i < party_size; i++)
	{
		party[i].base_stats.current_hp += heal_amount;
		if (party[i].base_stats.current_hp > party[i].base_stats.max_hp)
		{
			party[i].base_stats.current_hp = party[i].base_stats.max_hp;
		}
	}

	printf("%s uses Heal Gadget! All allies healed by %d HP!\n", user->base_stats.name, heal_amount);
}

void sr_damage_gadget(CharacterSheet *user, CharacterSheet party[], uchar party_size, CreatureSheet enemies[], uchar enemy_count)
{
	uint damage_amount = 15 + user->base_stats.intellect;
	for (int i = 0; i < enemy_count; i++)
	{
		enemies[i].base_stats.current_hp -= damage_amount;
	}

	printf("%s uses Damage Gadget! All enemies take %d damage!\n", user->base_stats.name, damage_amount);
}

void sr_init_gadgets()
{
	gadgets[0].name = "Heal Gadget";
	gadgets[0].effect = sr_heal_gadget;
	gadgets[0].uses = 3;

	gadgets[1].name = "Damage Gadget";
	gadgets[1].effect = sr_damage_gadget;
	gadgets[1].uses = 2;

	// Initialize more gadgets as needed...
}
