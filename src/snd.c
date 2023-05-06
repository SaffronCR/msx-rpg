//------------------------------------------------------------------
// Star Rangers - A Dungeon Crawler for MSX2 using Fusion-C
//------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fusion-c/header/msx_fusion.h"
#include "fusion-c/header/ayfx_player.h"
#include "fusion-c/header/pt3replayer.h"

#include "main.h"
#include "snd.h"

//------------------------------------------------------------------
// Variables.
//------------------------------------------------------------------

uchar is_playing_song;

//------------------------------------------------------------------
// Functions.
//------------------------------------------------------------------

void sr_init_snd(void)
{
	sr_init_dungeon_song();
	is_playing_song = TRUE;

	//is_playing_song = FALSE;
}

void sr_update_snd(void)
{
	// Update audio.
	if (is_playing_song == TRUE)
	{
		sr_play_song();
	}
}
