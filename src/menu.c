//------------------------------------------------------------------
// Star Rangers - A Dungeon Crawler for MSX2 using Fusion-C
//------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fusion-c/header/msx_fusion.h"

#include "main.h"
#include "gfx.h"
#include "fnt.h"
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
struct OptionMenu *current_menu;

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

void sr_set_current_menu(struct OptionMenu *menu, uchar menu_option, uchar num_options, uchar x, uchar y)
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

	for (uchar i = 0; i < 2; i++)
	{
		switch (JoystickRead(i))
		{
			case UP: 
				if (current_menu_option > 0)
				{
					current_menu_option--;
					menu_option_changed = true;
				}
				break;

			case DOWN:
				if (current_menu_option < current_num_options - 1)
				{
					current_menu_option++;
					menu_option_changed = true;	
				}
				break;
		}
	}
	
	if (TriggerRead(JOY1_BUTTONA) == PRESSED || TriggerRead(SPACEBAR) == PRESSED)
	{
		current_menu[current_menu_option].function();		
	}
	else if (TriggerRead(JOY1_BUTTONB) == PRESSED  ||  GetKeyMatrix(6) == 0b11111011) // GRAPH key.
	{
		return true;
	}
	else if (menu_option_changed == true)
	{
		sr_draw_current_menu();
	}

	return false;
}
