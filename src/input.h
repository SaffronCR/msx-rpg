//------------------------------------------------------------------
// Star Rangers - A Dungeon Crawler for MSX2 using Fusion-C
//------------------------------------------------------------------

#ifndef INPUT_H
#define INPUT_H

#include "main.h"

//------------------------------------------------------------------
// Enums.
//------------------------------------------------------------------

enum Dpad
{
	DPAD_NONE,
	DPAD_UP,
	DPAD_RIGHT,
	DPAD_DOWN,
	DPAD_LEFT
};

//------------------------------------------------------------------
// Prototypes.
//------------------------------------------------------------------

void sr_init_input(void);
void sr_update_input(void);

enum Dpad sr_input_read_dpad_continuous(void);
enum Dpad sr_input_read_dpad_first_press(void);
bool sr_input_read_accept(void);
bool sr_input_read_cancel(void);

// Debug.

bool sr_debug_input_read_regen_dungeon(void);

#endif
