//------------------------------------------------------------------
// Star Rangers - A Dungeon Crawler for MSX2 using Fusion-C
//------------------------------------------------------------------

#ifndef SYSTEM_H
#define SYSTEM_H

#include "main.h"

//------------------------------------------------------------------
// Prototypes.
//------------------------------------------------------------------

void sf_error_handler(uchar n, uchar *name);
void sf_set_name(FCB *p_fcb, const uchar *p_name);
void sf_wait(uint cicles);

#endif
