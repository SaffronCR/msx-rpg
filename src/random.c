//------------------------------------------------------------------
// Star Rangers - A Dungeon Crawler for MSX2 using Fusion-C
//------------------------------------------------------------------

#include "random.h"

//------------------------------------------------------------------
// Variables.
//------------------------------------------------------------------

uint xs = 1;

//------------------------------------------------------------------
// Functions.
//------------------------------------------------------------------

void sr_random_init(uint seed)
{
	xs = seed | 0x8000; // Make sure seed is never zero.
}

// 16-bit xorshift PRNG.
uint sr_random(void)
{
	xs ^= xs << 7;
	xs ^= xs >> 9;
	xs ^= xs << 8;

	return (xs);
}

// Generate a pseudo-random number between min and max (inclusive).
uint sr_random_range(uint min, uint max)
{
	return (sr_random() % (max + 1 - min) + min);
}

// Generate a pseudo-random number between min and max (inclusive) using rejection sampling (for smaller numbers).
uint sr_random_range_small(uint min, uint max)
{
    uint range = max - min + 1;
    uint value = 0;
    do
	{
		value = sr_random() % (range * 2);
    } while (value >= range * 2);
    value *= 0.5;
    value += min;

    return (value);
}
