//------------------------------------------------------------------
// Star Rangers - A Dungeon Crawler for MSX2 using Fusion-C
//------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fusion-c/header/msx_fusion.h"

#include "system.h"

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
		printf("\n\rSORRY: this game does not work on %s", name);
		break;
	}

	Exit(0);
}

// Set the name of a file to load (MSX DOS).
void sr_set_name(FCB *p_fcb, const uchar *p_name)
{
	uchar i, j;
	memset(p_fcb, 0, sizeof(FCB));

	for (i = 0; i < 11; i++)
	{
		p_fcb->name[i] = ' ';
	}

	for (i = 0; (i < 8) && (p_name[i] != 0) && (p_name[i] != '.'); i++)
	{
		p_fcb->name[i] = p_name[i];
	}

	if (p_name[i] == '.')
	{
		i++;
		for (j = 0; (j < 3) && (p_name[i + j] != 0) && (p_name[i + j] != '.'); j++)
		{
			p_fcb->ext[j] = p_name[i + j];
		}
	}
}

void sr_wait(uint cicles)
{
	for (uint i = 0; i < cicles; i++)
	{
		__asm halt __endasm;
	}
}
