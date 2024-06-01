//------------------------------------------------------------------
// Star Rangers - A Dungeon Crawler for MSX2 using Fusion-C
//------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fusion-c/header/msx_fusion.h"

#include "gfx.h"
#include "fnt.h"
#include "input.h"
#include "menu.h"

//------------------------------------------------------------------
// Defines.
//------------------------------------------------------------------

#define MENU_FONT_COLOR 15
#define MENU_BG_COLOR 0
#define MENU_BG_COLOR_SELECTED 8

//------------------------------------------------------------------
// Variables.
//------------------------------------------------------------------

uchar current_menu_option;
OptionMenu *current_menu;

uchar current_num_options;

uchar current_menu_x;
uchar current_menu_y;

//------------------------------------------------------------------
// Functions.
//------------------------------------------------------------------

void sr_draw_current_menu(void)
{
	uchar x = current_menu_x;
	uchar y = current_menu_y;

	for (uchar option = 0; option < current_num_options; option++)
	{
		sr_draw_text(current_menu[option].text,
		FONT_SIZE * x, FONT_SIZE * y,
		MENU_FONT_COLOR,
		option == current_menu_option ? MENU_BG_COLOR_SELECTED : MENU_BG_COLOR);

		y++;
	}
}

void sr_set_current_menu(OptionMenu *menu, uchar menu_option, uchar num_options, uchar x, uchar y)
{
	current_menu = menu;
	current_menu_option = menu_option;
	current_num_options = num_options;
	current_menu_x = x;
	current_menu_y = y;

	sr_draw_current_menu();
}

bool sr_update_current_menu(void)
{
	bool menu_option_changed = false;

	switch (sr_input_read_dpad())
	{
		case DPAD_UP:
			if (current_menu_option > 0)
			{
				current_menu_option--;
				menu_option_changed = true;
			}
			break;

		case DPAD_DOWN:
			if (current_menu_option < current_num_options - 1)
			{
				current_menu_option++;
				menu_option_changed = true;
			}
			break;
	}

	if (sr_input_read_accept() == true)
	{
		current_menu[current_menu_option].function();
	}
	else if (sr_input_read_cancel() == true)
	{
		return true;
	}
	else if (menu_option_changed == true)
	{
		sr_draw_current_menu();
	}

	return false;
}
