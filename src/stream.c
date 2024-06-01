//------------------------------------------------------------------
// Star Rangers - A Dungeon Crawler for MSX2 using Fusion-C
//------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stream.h"

//------------------------------------------------------------------
// Variables.
//------------------------------------------------------------------

Stream streams[MAX_STREAMS];

//------------------------------------------------------------------
// Functions.
//------------------------------------------------------------------

void sr_boost_signal(CharacterSheet *streamer, CharacterSheet party[], uchar party_size, CreatureSheet enemies[], uchar enemy_count)
{
	for (int i = 0; i < party_size; i++)
	{
		party[i].base_stats.might += 2 + (streamer->base_stats.personality / 2);
	}

	printf("%s uses Boost Signal! All allies' Might increased!\n", streamer->base_stats.name);
}

void sr_distract_signal(CharacterSheet *streamer, CharacterSheet party[], uchar party_size, CreatureSheet enemies[], uchar enemy_count)
{
	for (int i = 0; i < enemy_count; i++)
	{
		enemies[i].defense -= 2 + (streamer->base_stats.personality / 2);
	}

	printf("%s uses Distract Signal! All enemies' Defense decreased!\n", streamer->base_stats.name);
}

void init_streams()
{
	streams[0].name = "Boost Signal";
	streams[0].effect = sr_boost_signal;
	streams[0].cooldown = 3;
	streams[0].current_cooldown = 0;

	streams[1].name = "Distract Signal";
	streams[1].effect = sr_distract_signal;
	streams[1].cooldown = 3;
	streams[1].current_cooldown = 0;

	// Initialize more streams as needed...
}
