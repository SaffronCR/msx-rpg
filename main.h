//------------------------------------------------------------------
// Star Rangers - A Dungeon Crawler for MSX2 using Fusion-C
//------------------------------------------------------------------

#ifndef MAIN_H
#define MAIN_H

//------------------------------------------------------------------
// Typedefs.
//------------------------------------------------------------------

typedef unsigned int uint;

//------------------------------------------------------------------
// Defines.
//------------------------------------------------------------------

#define FALSE 0
#define TRUE 1

#define BUFFER_SIZE 4608

#define JOY_UP 1
#define JOY_DOWN 5
#define JOY_LEFT 7
#define JOY_RIGHT 3

#define SPACE_KEY 0
#define JOY_1 1
#define JOY_2 3

//------------------------------------------------------------------
// Enums.
//------------------------------------------------------------------

enum DoubleBufferState
{
	Updating,
	ReadyToSwitch,
	Finished
};

//------------------------------------------------------------------
// Variables.
//------------------------------------------------------------------

extern char back_page;

extern enum DoubleBufferState db_state;

//------------------------------------------------------------------
// Prototypes.
//------------------------------------------------------------------

void sf_screen_copy(uint x1, uint y1, uint dx, uint dy, uint x2, uint y2, uint src_pg, uint dst_pg, char mode);

// Debug.

void sf_draw_palette(void);

#endif
