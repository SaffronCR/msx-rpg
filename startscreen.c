//------------------------------------------------------------------
// Star Rangers - A Dungeon Crawler for MSX2 using Fusion-C
//------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fusion-c/header/msx_fusion.h"
#include "fusion-c/header/vdp_sprites.h"
#include "fusion-c/header/vdp_graph2.h"

#include "main.h"
#include "startscreen.h"

void sf_draw_startscreen_intro_text(void)
{
	// Intro text.
    db_state = Updating;
    Cls();
	SetColors(15, 0, 0);
    db_state = ReadyToSwitch;
    PutText(8*7, 100, "SAFFRON SOFT  2020", LOGICAL_IMP);

    PutText(0, 90, "********************************", LOGICAL_IMP);

    sf_wait(200);

	// Main menu text.
    db_state = Updating;
    Cls();
	SetColors(15, 0, 0);
    PutText(8*7, 100, "Start", LOGICAL_IMP);
    PutText(8*7, 120, "Load", LOGICAL_IMP);
    db_state = ReadyToSwitch;
}

void sf_set_startscreen_mode(void)
{
    sf_draw_startscreen_intro_text();
}

void sf_update_startscreen_mode(void)
{
}
