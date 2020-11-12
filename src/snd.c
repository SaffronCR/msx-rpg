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

char is_playing_song = FALSE;

//------------------------------------------------------------------
// Functions.
//------------------------------------------------------------------

void sf_update_audio(void)
{
	// Update audio.
	if (is_playing_song == TRUE)
	{
		sf_play_song();
	}
}
