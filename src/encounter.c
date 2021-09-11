//------------------------------------------------------------------
// Star Rangers - A Dungeon Crawler for MSX2 using Fusion-C
//------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fusion-c/header/msx_fusion.h"
#include "fusion-c/header/vdp_sprites.h"
#include "fusion-c/header/vdp_graph2.h"

#include "encounter.h"

//------------------------------------------------------------------
// Defines.
//------------------------------------------------------------------

#define ENCOUNTER_ARRAY_SIZE 256

//------------------------------------------------------------------
// Variables.
//------------------------------------------------------------------

const uchar encounter_table[ENCOUNTER_ARRAY_SIZE] =
{
    0x1F, 0xA6, 0xDE, 0xBA, 0xCC, 0x12, 0x7D, 0x74, 0x1B, 0xF3, 0xB4, 0x88, 0xF8, 0x52, 0xF4, 0x07,
    0x90, 0xAB, 0xB3, 0xBD, 0xAA, 0x55, 0x28, 0xBC, 0x8A, 0x6D, 0x0E, 0xC4, 0x83, 0xA9, 0x3B, 0x76,
    0x20, 0x7C, 0x09, 0x92, 0xFD, 0x4A, 0xA8, 0xF0, 0x61, 0xE3, 0xF2, 0x69, 0x6C, 0xBB, 0x38, 0xC3,
    0xAE, 0xB7, 0x43, 0x84, 0x78, 0x23, 0x7B, 0x9B, 0x2D, 0xDB, 0x3E, 0x91, 0xCF, 0x02, 0x2A, 0xB6,
    0x86, 0xEE, 0x9C, 0x8E, 0xB8, 0x6F, 0x1A, 0x57, 0x05, 0xE9, 0x73, 0x31, 0xD2, 0xD9, 0x1D, 0xFB,
    0x94, 0x9D, 0xB1, 0x0A, 0x3A, 0x11, 0x5A, 0x47, 0x95, 0x2C, 0x44, 0xE0, 0x6A, 0x8C, 0x5B, 0x7A,
    0xA7, 0x5D, 0x36, 0x70, 0xE5, 0xC7, 0x49, 0xDC, 0x68, 0x97, 0xD8, 0x66, 0xA3, 0x0F, 0xB0, 0x9F,
    0x03, 0xD6, 0x77, 0x16, 0x13, 0x30, 0x25, 0x3C, 0x10, 0x17, 0xAD, 0x98, 0x6B, 0x2F, 0xD7, 0xA1,
    0xFF, 0xA4, 0xEB, 0x51, 0xFE, 0x27, 0x8D, 0x93, 0xD5, 0x3D, 0xF6, 0x08, 0x75, 0xE1, 0xA5, 0x46,
    0x63, 0xF5, 0x4D, 0xDA, 0x32, 0xAF, 0x40, 0x37, 0xD3, 0xC0, 0x89, 0x67, 0x06, 0x21, 0x6E, 0x81,
    0xB5, 0xA0, 0x4F, 0x0C, 0x2E, 0xE7, 0x1C, 0x58, 0x85, 0xE8, 0x59, 0xCE, 0x35, 0xCB, 0x1E, 0xC6,
    0x2B, 0x9A, 0xE6, 0xDD, 0xF1, 0xEC, 0x96, 0xCA, 0xAC, 0x00, 0x50, 0xC9, 0x4C, 0xFC, 0x14, 0x7E,
    0x56, 0x80, 0xD0, 0x79, 0xBF, 0x29, 0x87, 0x48, 0x24, 0x19, 0xC5, 0x22, 0x71, 0x7F, 0x72, 0x0D,
    0xCD, 0x8F, 0xBE, 0x3F, 0x9E, 0x34, 0xED, 0x53, 0x54, 0x04, 0x62, 0xA2, 0xC2, 0x41, 0x5E, 0x82,
    0x4B, 0x26, 0x5C, 0x42, 0x65, 0x99, 0x4E, 0x60, 0x8B, 0xF7, 0x0B, 0x33, 0xDF, 0xD1, 0x64, 0xC8,
    0xC1, 0x01, 0xEF, 0xF9, 0xFA, 0xE4, 0x5F, 0x18, 0xB9, 0xB2, 0x39, 0xD4, 0x15, 0xE2, 0xEA, 0x45
};

uchar current_step;
uchar current_threshold;

//------------------------------------------------------------------
// Functions.
//------------------------------------------------------------------

void sf_init_encounter(void)
{
    current_step = 0;
    current_threshold = 10;
}

void sf_encounter_step(void)
{
    current_step++;
}

BOOL sf_check_encounter(void)
{
    return (encounter_table[current_step] < current_threshold);
}
