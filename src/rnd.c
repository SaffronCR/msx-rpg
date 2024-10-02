//------------------------------------------------------------------
// Star Rangers - A Dungeon Crawler for MSX2 using Fusion-C
//------------------------------------------------------------------

#include "rnd.h"

//------------------------------------------------------------------
// Variables.
//------------------------------------------------------------------

uint a = 13;
uint b = 5;
uint c = 10;
uint d = 9;

uint s0 = 1; // Must use 16-bit variable.
uint s1 = 0; // Must use 16-bit variable.

//------------------------------------------------------------------
// Functions.
//------------------------------------------------------------------

// Initializes the seed.
void sr_init_seed(uint seed)
{
	s0 = seed;
	s1 = ~seed;
}

// Rotate left by 'k' bits within 16 bits.
uint sr_rol(uint x, uint k)
{
	return (x << k) | (x >> (16 - k));
}

// Pseudorandom number generator using a xoroshiro16++ algorithm.
uint sr_xoroshiro16(void)
{
	uint result = sr_rol(s0 + s1, d) + s0;

	s1 ^= s0;
	s0 = sr_rol(s0, a) ^ s1 ^ (s1 << b);
	s1 = sr_rol(s1, c);

	return result;
}

// Returns a pseudorandom number within min and max (inclusive).
uint sr_random_range(uint min, uint max)
{
	return (sr_xoroshiro16() % (max + 1 - min) + min);
}

// Returns the result of rolling a [sides] die (1 to [sides]).
uint sr_random_die(uint sides)
{
	return (sr_xoroshiro16() % sides) + 1;
}
