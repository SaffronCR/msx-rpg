//------------------------------------------------------------------
// Star Rangers - A Dungeon Crawler for MSX2 using Fusion-C
//------------------------------------------------------------------

#ifndef STARTSCR_H
#define STARTSCR_H

#include "main.h"

//------------------------------------------------------------------
// Defines.
//------------------------------------------------------------------

#define TITLE_PAGE 0

//------------------------------------------------------------------
// Prototypes.
//------------------------------------------------------------------

void sr_load_game(void);
void sr_new_game(void);
void sr_set_startscr_state(void);
void sr_update_startscr_state(void);
void sr_finished_startscr_drawing(void);

#endif
