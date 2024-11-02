//------------------------------------------------------------------
// Star Rangers - A Dungeon Crawler for MSX2 using Fusion-C
//------------------------------------------------------------------

#include "fusion-c/header/msx_fusion.h"

#include "input.h"

//------------------------------------------------------------------
// Variables.
//------------------------------------------------------------------

enum Dpad dpad_state;
uchar a_button_state;
uchar b_button_state;
uchar space_key_state;
uchar key_matrix_state;

bool dpad_pressed;
bool accept_pressed;
bool cancel_pressed;

//------------------------------------------------------------------
// Functions.
//------------------------------------------------------------------

void sr_init_input(void)
{
	dpad_state = DPAD_NONE;
	a_button_state = 0;
	b_button_state = 0;
	space_key_state = 0;
	key_matrix_state = 0;

	dpad_pressed = false;
	accept_pressed = false;
	cancel_pressed = false;
}

void sr_update_input(void)
{
	dpad_state = JoystickRead(0);
	a_button_state = TriggerRead(JOY1_BUTTONA);
	b_button_state = TriggerRead(JOY1_BUTTONB);
	space_key_state = TriggerRead(SPACEBAR);
	//key_matrix_state = GetKeyMatrix(4); // this call is to slow, check for alternatives.
}

enum Dpad sr_get_dpad_state(void)
{
	return dpad_state;
}

uchar sr_get_a_button_state(void)
{
	return a_button_state;
}

uchar sr_get_b_button_state(void)
{
	return b_button_state;
}

uchar sr_get_space_key_state(void)
{
	return space_key_state;
}

uchar sr_get_key_matrix_state(void)
{
	return key_matrix_state;
}

enum Dpad sr_input_read_dpad_continuous(void)
{¡
	switch (sr_get_dpad_state())
	{
		case UP:	return DPAD_UP;		break;
		case RIGHT:	return DPAD_RIGHT;	break;
		case DOWN:	return DPAD_DOWN;	break;
		case LEFT:	return DPAD_LEFT;	break;
	}

	return DPAD_NONE;
}

// Read D-Pad input and trigger only on press-release cycles.
enum Dpad sr_input_read_dpad_first_press(void)
{
	static enum Dpad last_dpad = DPAD_NONE;
	enum Dpad current_dpad = DPAD_NONE;

	switch (sr_get_dpad_state())
	{
		case UP:	current_dpad = DPAD_UP;		break;
		case RIGHT:	current_dpad = DPAD_RIGHT;	break;
		case DOWN:	current_dpad = DPAD_DOWN;	break;
		case LEFT:	current_dpad = DPAD_LEFT;	break;
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
	bool current_accept = (sr_get_a_button_state() == PRESSED ||
							sr_get_space_key_state() == PRESSED);

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
	bool current_cancel = (sr_get_b_button_state() == PRESSED ||
		sr_get_key_matrix_state() == 0b11111011 ||	// 'N' key.
		sr_get_key_matrix_state() == 0b11111101);	// 'M' key.

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
		return (sr_get_key_matrix_state() == 0b01111111); // 'R' key.
}
