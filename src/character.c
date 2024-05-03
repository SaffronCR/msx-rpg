//------------------------------------------------------------------
// Star Rangers - A Dungeon Crawler for MSX2 using Fusion-C
//------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fusion-c/header/msx_fusion.h"

#include "main.h"
#include "character.h"


//------------------------------------------------------------------
// Functions.
//------------------------------------------------------------------

void sr_add_damage_type(uchar *mask, enum DamageType type)
{
    *mask |= (1 << type);
}

int sr_has_damage_type(uchar mask, enum DamageType type)
{
    return mask & (1 << type);
}

// Examples.
// {
// 	uchar mask;
// 	sr_add_damage_type(&mask, DT_KINETIC);
//	sr_add_damage_type(&mask, DT_ENERGY);

//	if (sr_has_damage_type(mask, DT_KINETIC) == true)
// 	{
//  	printf("Damage type includes Kinetic.\n");
//	}

// 	if (sr_has_damage_type(mask, DT_ENERGY) == true)
// 	{
//  	printf("Damage type includes Energy.\n");
//	}

//	if (sr_has_damage_type(mask, DT_KINETIC | DT_ENERGY) == false)
// 	{
//  	printf("Damage type doesn't include both Kinetic and Energy.\n");
//	}
// }

void sr_debug_create_default_character(struct CharacterSheet *character)
{
    // Initialize base stats.
    strcpy(character->base_stats.name, "Lisbeth");
    character->base_stats.level = 1;
    character->base_stats.might = 10;
    character->base_stats.dexterity = 10;
    character->base_stats.intellect = 10;
    character->base_stats.personality = 10;
    character->base_stats.max_hp = 100;
    character->base_stats.current_hp = 100;

	// Initialize character stats.
    character->race = RACE_TOREM;
    character->job = JOB_PIRATE;
    character->current_xp = 0;
    character->equipped_melee_weapon = MW_NONE;
    character->equipped_ranged_weapon = RW_NONE;
    character->equipped_armor = ARMOR_NONE;
}

void sr_debug_create_default_creature(struct CreatureSheet *creature)
{
    // Initialize base stats.
    strcpy(creature->base_stats.name, "Starjelly");
    creature->base_stats.level = 1;
    creature->base_stats.might = 6;
    creature->base_stats.dexterity = 10;
    creature->base_stats.intellect = 3;
    creature->base_stats.personality = 3;
    creature->base_stats.max_hp = 6;
    creature->base_stats.current_hp = 6;

    // Initialize creature stats.
    creature->kinetic_resistance = DR_NONE;
    creature->energy_resistance = DR_STRONG;
    creature->damage_roll = DMG_1D4;
	creature->damage_type = DT_KINETIC;
    creature->defense = 10;
}
