//------------------------------------------------------------------
// Star Rangers - A Dungeon Crawler for MSX2 using Fusion-C
//------------------------------------------------------------------

#include "random.h"

//------------------------------------------------------------------
// Variables.
//------------------------------------------------------------------

uint a = 13;
uint b = 5;
uint c = 10;
uint d = 9;

uint s0 = 1;
uint s1 = 0;

//------------------------------------------------------------------
// Functions.
//------------------------------------------------------------------

uint sr_rol(uint x, uint k)
{
	return (x << k) | (x >> ((sizeof(x) * 8) - k));
}

// Pseudorandom number generator using a xoroshiro32++ algorithm.
uint sr_xoroshiro32(void)
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
	return (sr_xoroshiro32() % (max + 1 - min) + min);
}

// Returns the result of rolling a [sides] die.
uint sr_random_die(uint sides)
{
	return (sr_xoroshiro32() % (sides + 1));
}
