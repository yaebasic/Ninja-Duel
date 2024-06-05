#pragma once

#include "defines.h"

#include <graphx.h>

// 3-byte entries = 24-bit data type (see explanation in images.cpp)
using LUT = u24;

// enumeration used to access individual sprites
enum Sprites
{
    SPRITE_IDLE_00,
    SPRITE_IDLE_01,

    SPRITE_LPUNCH_00,
    SPRITE_LPUNCH_01,

    SPRITE_RPUNCH_00,
    SPRITE_RPUNCH_01,

    // avoid a separate #define
    SPRITE_COUNT
};

class Images
{

public:

    // loads sprite data into memory
    Images();

    // returns a sprite pointer given `index` parameter
    const gfx_rletsprite_t *getSprite(u8 index) const;

private:

    // Initializes color palette
    void loadPalette() const;

    // Initializes sprite data into memory
    void loadSprites();

    // \returns the memory location of an LUT entry given `lut_entry` parameter
    const u8 *getDataPtr(u8 lut_entry) const;

    // \returns the size of an LUT entry given `lut_entry` parameter
    LUT getDataSize(u8 lut_entry) const;

    // stores the pointers of sprite data extracted into memory
    gfx_rletsprite_t *m_images[SPRITE_COUNT];

    // handle id used to open the appvar
    u8 m_appvar;

    // start of appvar; reference point to add LUT offsets onto
    // (i.e., lut_ptr + offset --> offset_ptr)
    LUT *m_lut_ptr;

};