#pragma once

#include "defines.h"

#include <graphx.h>

#define NINJA_SPRITE_WIDTH  32
#define NINJA_SPRITE_HEIGHT 32

// 3-byte entries = 24-bit data type (see explanation in images.cpp)
using LUT = u24;

enum Sprites
{
    SPRITE_IDLE_00,
    SPRITE_IDLE_01,
    SPRITE_IDLE_02,

    // avoid a separate #define
    SPRITE_CNT
};

class Images
{

public:

    // should be run before any image functions are called;
    // loads sprite data into memory
    void extract();

    // returns a sprite pointer given `index` parameter
    const gfx_rletsprite_t *getSprite(u8 index);

private:

    // Initializes color palette
    void loadPalette();

    // Initializes sprite data into memory
    void loadSprites();

    // \returns the memory pointer of an LUT entry given `lut_entry` parameter
    const u8 *getDataPtr(u8 lut_entry);

    // \returns the size of an LUT entry given `lut_entry` parameter
    u24 getDataSize(u8 lut_entry);

    // stores the pointers of sprite data extracted into memory
    const gfx_rletsprite_t *images[SPRITE_CNT];

    // handle id used to open the appvar
    u8 appvar;

    // immutable as its sole use is as a reference point to add LUT offsets
    // \note (lut_ptr + offset --> offset_ptr) is what we're after
    // \note is set to the first byte of the LookUp Table in init()
    const LUT *lut_ptr;

};