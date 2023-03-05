//------------------------------------------------------------------
// Star Rangers - A Dungeon Crawler for MSX2 using Fusion-C
//------------------------------------------------------------------

#ifndef RANDOM_H
#define RANDOM_H

#include "main.h"

//------------------------------------------------------------------
// Prototypes.
//------------------------------------------------------------------

void sr_random_init(uint seed);
uint sr_random(void);
uint sr_random_range(uint min, uint max);
uint sr_random_range_small(uint min, uint max);

#endif
