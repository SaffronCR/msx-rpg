#ifndef MAIN_H
#define MAIN_H

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

//------------------------------------------------------------------
// Enums.
//------------------------------------------------------------------

enum DoubleBufferState
{
	Updating,
	ReadyToTransfer,
	Transfering,
	Finished
};

//------------------------------------------------------------------
// Variables.
//------------------------------------------------------------------

extern enum DoubleBufferState db_state;

//------------------------------------------------------------------
// Prototypes.
//------------------------------------------------------------------

void sf_screen_copy(int x1, int y1, int dx, int dy, int x2, int y2, int src_pg, int dst_pg, int mode);

#endif
