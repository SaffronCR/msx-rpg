//------------------------------------------------------------------
// Star Rangers - A Dungeon Crawler for MSX2 using Fusion-C
//------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fusion-c/header/msx_fusion.h"

#include "system.h"

//------------------------------------------------------------------
// Defines.
//------------------------------------------------------------------

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

//------------------------------------------------------------------
// Functions.
//------------------------------------------------------------------

// In case of Error.
void sr_error_handler(uchar n, uchar *name)
{
	InitPSG();
	Screen(0);
	SetColors(15, 6, 6);

	switch (n)
	{
		case 1:
			printf("\n\rFAILED: fcb_open(): %s ", name);
			break;

		case 2:
			printf("\n\rFAILED: fcb_close(): %s", name);
			break;

		case 3:
			printf("\n\rSORRY: This game does not work on %s", name);
			break;

		case 4:
			printf("\n\rNOT SUPPORTED: %s", name);
			break;
	}

	Exit(EXIT_FAILURE);
}

// Set the name of a file to load (MSX DOS).
void sr_set_name(FCB *p_fcb, const uchar *p_name)
{
	uchar i = 0;
	uchar j = 0;

	// Clear the FCB structure.
	memset(p_fcb, 0, sizeof(FCB));

	// Initialize name to spaces.
	for (i = 0; i < 11; i++)
	{
		p_fcb->name[i] = ' ';
	}

	// Set the filename (up to 8 characters).
	for (i = 0; (i < 8) && (p_name[i] != 0) && (p_name[i] != '.'); i++)
	{
		p_fcb->name[i] = p_name[i];
	}

	// Check if there's an extension.
	if (p_name[i] == '.')
	{
		i++; // Move past the dot.
		for (j = 0; (j < 3) && (p_name[i + j] != 0); j++)
		{
			p_fcb->ext[j] = p_name[i + j];
		}
	}

	// Fill the remaining name characters with spaces.
	for (; i < 8; i++)
	{
		p_fcb->name[i] = ' ';
	}

	// Fill the remaining extension characters with spaces.
	for (; j < 3; j++)
	{
		p_fcb->ext[j] = ' ';
	}
}

void sr_wait(uint cicles)
{
	for (uint i = 0; i < cicles; i++)
	{
		__asm halt __endasm;
	}
}

bool loading;

void sr_set_loading(bool state)
{
	loading = state;
}

bool sr_is_loading(void)
{
	return loading;
}
