//------------------------------------------------------------------
// Star Rangers - A Dungeon Crawler for MSX2 using Fusion-C
//------------------------------------------------------------------

#ifndef SYSTEM_H
#define SYSTEM_H

#include "main.h"

//------------------------------------------------------------------
// Prototypes.
//------------------------------------------------------------------

void sr_error_handler(uchar n, uchar *name);
void sr_set_name(FCB *p_fcb, const uchar *p_name);
void sr_wait(uint cicles);
void sr_set_loading(bool state);
bool sr_is_loading(void);

#endif
