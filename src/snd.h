//------------------------------------------------------------------
// Star Rangers - A Dungeon Crawler for MSX2 using Fusion-C
//------------------------------------------------------------------

#ifndef SND_H
#define SND_H

#include "main.h"

//------------------------------------------------------------------
// Prototypes.
//------------------------------------------------------------------

void sr_init_snd(void);
void sr_update_snd(void);
void sr_stop_music(void);
void sr_play_exploration_music(void);
void sr_play_battle_music(void);
void sr_init_song(void);
void sr_play_song(void);
void sr_stop_song(void);
void sr_init_dungeon_song(void);
void sr_init_battle_song(void);

#endif
