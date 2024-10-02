//------------------------------------------------------------------
// Star Rangers - A Dungeon Crawler for MSX2 using Fusion-C
//------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fusion-c/header/msx_fusion.h"
#include "fusion-c/header/ayfx_player.h"
#include "fusion-c/header/pt3replayer.h"

#include "system.h"
#include "snd.h"

//------------------------------------------------------------------
// Enums.
//------------------------------------------------------------------

enum Music
{
	MUSIC_NONE,
	MUSIC_EXPLORATION,
	MUSIC_BATTLE
};

//------------------------------------------------------------------
// Variables.
//------------------------------------------------------------------

enum Music next_music;
enum Music current_music;

//------------------------------------------------------------------
// Functions.
//------------------------------------------------------------------

void sr_init_snd(void)
{
	next_music = MUSIC_NONE;
	current_music = MUSIC_NONE;
}

void sr_update_snd(void)
{
	if (current_music != next_music)
	{
		current_music = next_music;
		switch (current_music)
		{
			case MUSIC_EXPLORATION: sr_init_dungeon_song(); break;
			case MUSIC_BATTLE: sr_init_battle_song(); break;
			case MUSIC_NONE: sr_stop_song(); break;
		}
	}

	// Update audio.
	if (current_music != MUSIC_NONE && sr_is_loading() == false)
	{
		sr_play_song();
	}
}

void sr_stop_music(void)
{
	next_music = MUSIC_NONE;
}

void sr_play_exploration_music(void)
{
	next_music = MUSIC_EXPLORATION;
}

void sr_play_battle_music(void)
{
	next_music = MUSIC_BATTLE;
}
