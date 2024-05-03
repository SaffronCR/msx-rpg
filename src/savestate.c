//------------------------------------------------------------------
// Star Rangers - A Dungeon Crawler for MSX2 using Fusion-C
//------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fusion-c/header/msx_fusion.h"

#include "main.h"
#include "system.h"
#include "savestate.h"

//------------------------------------------------------------------
// Variables.
//------------------------------------------------------------------

//------------------------------------------------------------------
// Functions.
//------------------------------------------------------------------

// bool sr_save_game_state(uchar *file_name, const struct GameState *state)
// {
//     // #TODO.

//     sr_set_name(&file, file_name);

// 	if (fcb_open(&file) != FCB_SUCCESS)
// 	{
// 		sr_error_handler(1, file_name);
// 		return (false);
// 	}

//     fcb_write(&file, state, sizeof(state));

// 	// Check for errors.
// 	if (fcb_close(&file) != FCB_SUCCESS)
// 	{
// 		sr_error_handler(2, file_name);
// 		return (false);
// 	}

// 	return (true);
// }

// bool sr_load_game_state(uchar *file_name, struct GameState *state)
// {
//     // #TODO.

//     sr_set_name(&file, file_name);

// 	if (fcb_open(&file) != FCB_SUCCESS)
// 	{
// 		sr_error_handler(1, file_name);
// 		return (false);
// 	}

//     fcb_read(&file, state, sizeof(state));

// 	// Check for errors.
// 	if (fcb_close(&file) != FCB_SUCCESS)
// 	{
// 		sr_error_handler(2, file_name);
// 		return (false);
// 	}

// 	return (true);
// }
