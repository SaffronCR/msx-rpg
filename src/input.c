//------------------------------------------------------------------
// Star Rangers - A Dungeon Crawler for MSX2 using Fusion-C
//------------------------------------------------------------------

#include "fusion-c/header/msx_fusion.h"

#include "input.h"

//------------------------------------------------------------------
// Functions.
//------------------------------------------------------------------

enum Dpad sr_input_read_dpad(void)
{
	for (uchar i = 0; i < 2; i++)
	{
		switch (JoystickRead(i))
		{
			case UP:	return DPAD_UP;		break;
			case RIGHT:	return DPAD_RIGHT;	break;
			case DOWN:	return DPAD_DOWN;	break;
			case LEFT:	return DPAD_LEFT;	break;
		}
	}

	return DPAD_NONE;
}

bool sr_input_read_accept(void)
{
	return (TriggerRead(JOY1_BUTTONA) == PRESSED ||
			TriggerRead(SPACEBAR) == PRESSED);
}

bool sr_input_read_cancel(void)
{
	return (TriggerRead(JOY1_BUTTONB) == PRESSED ||
			GetKeyMatrix(6) == 0b11111011 ||	// 'GRAPH' key.
			GetKeyMatrix(4) == 0b11111011 ||	// 'N' key.
			GetKeyMatrix(4) == 0b11111101);		// 'M' key.
}

bool sr_debug_input_read_regen_dungeon(void)
{
		return (GetKeyMatrix(4) == 0b01111111); // 'R' key.
}
