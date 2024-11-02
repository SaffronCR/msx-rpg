//------------------------------------------------------------------
// Star Rangers - A Dungeon Crawler for MSX2 using Fusion-C
//------------------------------------------------------------------

#ifndef RND_H
#define RND_H

#include "main.h"

//------------------------------------------------------------------
// Prototypes.
//------------------------------------------------------------------

void sr_init_seed(uint seed);
uint sr_random_range(uint min, uint max);
uint sr_random_die(uint sides);

#endif
