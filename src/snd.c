//------------------------------------------------------------------
// Star Rangers - A Dungeon Crawler for MSX2 using Fusion-C
//------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fusion-c/header/msx_fusion.h"
#include "fusion-c/header/ayfx_player.h"
#include "fusion-c/header/pt3replayer.h"

#include "snd.h"

//------------------------------------------------------------------
// Variables.
//------------------------------------------------------------------

bool is_playing_music;

//------------------------------------------------------------------
// Functions.
//------------------------------------------------------------------

void sr_init_snd(void)
{
	is_playing_music = false;
}

void sr_update_snd(void)
{
	// Update audio.
	if (is_playing_music == true)
	{
		sr_play_song();
	}
}

void sr_stop_music(void)
{
	is_playing_music = false;
}

void sr_play_dungeon_exploration_music(void)
{
	sr_init_dungeon_song();
	is_playing_music = true;
}
