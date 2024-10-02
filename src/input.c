//------------------------------------------------------------------
// Star Rangers - A Dungeon Crawler for MSX2 using Fusion-C
//------------------------------------------------------------------

#include "fusion-c/header/msx_fusion.h"

#include "input.h"

//------------------------------------------------------------------
// Variables.
//------------------------------------------------------------------

bool dpad_pressed;
bool accept_pressed;
bool cancel_pressed;

//------------------------------------------------------------------
// Functions.
//------------------------------------------------------------------

void sr_init_input(void)
{
	dpad_pressed = false;
	accept_pressed = false;
	cancel_pressed = false;
}

enum Dpad sr_input_read_dpad_continuous(void)
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

// Read D-Pad input and trigger only on press-release cycles.
enum Dpad sr_input_read_dpad_first_press(void)
{
	static enum Dpad last_dpad = DPAD_NONE;
	enum Dpad current_dpad = DPAD_NONE;

	for (uchar i = 0; i < 2; i++)
	{
		switch (JoystickRead(i))
		{
			case UP:	current_dpad = DPAD_UP;		break;
			case RIGHT:	current_dpad = DPAD_RIGHT;	break;
			case DOWN:	current_dpad = DPAD_DOWN;	break;
			case LEFT:	current_dpad = DPAD_LEFT;	break;
		}
	}

	// Trigger only on the first press and wait for release.
	if (current_dpad != DPAD_NONE && last_dpad == DPAD_NONE)
	{
		last_dpad = current_dpad;
		return current_dpad;
	}
	else if (current_dpad == DPAD_NONE)
	{
		// Reset when released.
		last_dpad = DPAD_NONE;
	}

	return DPAD_NONE;
}

// Read the "accept" input and trigger only on press-release cycles.
bool sr_input_read_accept(void)
{
	bool current_accept = (TriggerRead(JOY1_BUTTONA) == PRESSED || TriggerRead(SPACEBAR) == PRESSED);

	// Trigger only on the first press and wait for release.
	if (current_accept && !accept_pressed)
	{
		accept_pressed = true;
		return true;
	}
	else if (!current_accept)
	{
		// Reset when the button is released.
		accept_pressed = false;
	}

	return false;
}

// Read the "cancel" input and trigger only on press-release cycles.
bool sr_input_read_cancel(void)
{
	bool current_cancel = (TriggerRead(JOY1_BUTTONB) == PRESSED ||
						  GetKeyMatrix(6) == 0b11111011 ||	// 'GRAPH' key.
						  GetKeyMatrix(4) == 0b11111011 ||	// 'N' key.
						  GetKeyMatrix(4) == 0b11111101);	// 'M' key.

	// Trigger only on the first press and wait for release.
	if (current_cancel && !cancel_pressed)
	{
		cancel_pressed = true;
		return true;
	}
	else if (!current_cancel)
	{
		// Reset when the button is released.
		cancel_pressed = false;
	}

	return false;
}

// Cheat.
bool sr_debug_input_read_regen_dungeon(void)
{
		return (GetKeyMatrix(4) == 0b01111111); // 'R' key.
}
