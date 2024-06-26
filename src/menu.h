//------------------------------------------------------------------
// Star Rangers - A Dungeon Crawler for MSX2 using Fusion-C
//------------------------------------------------------------------

#ifndef MENU_H
#define MENU_H

#include "main.h"

//------------------------------------------------------------------
// Typedefs.
//------------------------------------------------------------------

typedef struct
{
	uchar text[20];
	void (*function)();
}  OptionMenu;

//------------------------------------------------------------------
// Prototypes.
//------------------------------------------------------------------

void sr_set_current_menu(OptionMenu *menu, uchar menu_option, uchar num_options, uchar x, uchar y);
bool sr_update_current_menu(void);

#endif
