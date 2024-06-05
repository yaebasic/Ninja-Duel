#pragma once

#include "defines.h"

#include <graphx.h>

// 3-byte LUT entries; change to u16 if 2-byte entries
using LUT = u24;

enum Sprites
{
    SPRITE_IDLE_00,
    SPRITE_IDLE_01,

    SPRITE_LPUNCH_00,
    SPRITE_LPUNCH_01,

    SPRITE_RPUNCH_00,
    SPRITE_RPUNCH_01,

    SPRITE_COUNT
};

class Images
{

public:

    Images();

    const gfx_rletsprite_t *getSprite(u8 index) const;

private:

    void loadPalette() const;
    void loadSprites();

    const u8 *getLutEntryPtr(u8 lut_entry) const;
    LUT getLutEntrySize(u8 lut_entry) const;

    // an array of sprite data pointers
    gfx_rletsprite_t *m_images[SPRITE_COUNT];

    // handle id used to open appvar
    u8 m_appvar;

    // start of appvar; reference point to add LUT offsets onto
    LUT *m_lut_ptr;

};