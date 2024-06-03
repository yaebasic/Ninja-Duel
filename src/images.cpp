#include "images.h"

#include <fileioc.h>
#include <graphx.h>

/**
 * Nearly every line is commented
 * ... so I don't lose my mind again (actually I might anyways)
 * ... so I understand what I wrote in 6 months
 * ... for, hmmmm, ah yes - didactic purposes :)
*/

// Image data is stored in an appvar. A LookUp Table (LUT) is embedded at the
// start of the file. Each entry is 3-bits and is structured as below:
//
//  `Entry 0`: Number of entries in the LUT
//  `Entry 1`: Byte offset to first entry (always points to the palette data)
//  `Entry 2`: Byte offset to second entry (points to the data of first sprite)
//  `Entry 3`: Byte offset to third entry (points to the data of second sprite)
//  ...
enum LUTOffsets
{
    LUT_ENTRY_CNT,
    LUT_OFFSET_PALETTE,
    LUT_OFFSET_SPRITES
};

constexpr char APPVAR_NAME[] = "NinjImg";

void Images::extract()
{
    appvar = ti_Open(APPVAR_NAME, "r");

    // ostensibly points lut_ptr to start of lut table (a.k.a. start of appvar)
    lut_ptr = (LUT*)ti_GetDataPtr(appvar);

    loadPalette();
    loadSprites();

    ti_Close(appvar);
}

const gfx_rletsprite_t *Images::getSprite(u8 index)
{
    return images[index];
}

void Images::loadPalette()
{
    // see explanation within function
    const u24 pal_size = getDataSize(LUT_OFFSET_PALETTE);

    // get the physical pointer of the palette
    const u8 *pal_ptr = getDataPtr(LUT_OFFSET_PALETTE);

    gfx_SetPalette(pal_ptr, pal_size, 0);
}

void Images::loadSprites()
{
    for (u8 i = 0; i < SPRITE_CNT; ++i)
    {
        // get the physical pointer of the sprite
        const u8 *spr_ptr = getDataPtr(LUT_OFFSET_SPRITES + i);

        // and store the sprite data pointer into the index
        images[i] = (gfx_rletsprite_t*)spr_ptr;
    }
}

const u8 *Images::getDataPtr(u8 lut_entry)
{
    // first entry isn't a byte offset, just the number of entries within LUT
    // should never be intentionally called, but here for safety
    if (!lut_entry)
    {
        return (u8*)lut_ptr;
    }

    // LUT entries      | 3-bytes
    // offset values    | 1-byte
    //      --> type conversion needed to determine phsyical pointer of LUT
    //          entry's data
    return (u8*)lut_ptr + *(lut_ptr + lut_entry);
}

u24 Images::getDataSize(u8 lut_entry)
{
    // lut_ptr is already pointing at the first byte of the LUT, which is its
    // number of entries
    const u8 entry_cnt = *(u8*)lut_ptr;

    // lut_entry == entry_cnt is an edge case. see explanation below.
    if (lut_entry != entry_cnt)
    {
        // see explanation at top of page.
        // if (file_ptr + LUT_OFFSET_PALETTE) points to the palette and
        //    (file_ptr + LUT_OFFSET_SPRITES) points to the first sprite
        // then the difference of these two pointers is the size of the palette
        return *(lut_ptr + lut_entry + 1)
             - *(lut_ptr + lut_entry    );
    }

    // size of last entry within LUT is special, because we cannot take the
    // offset of the next entry as it does not exist. instead, find the size
    // of the whole appvar and subtract the offset of the pointer in question
    return ti_GetSize(appvar) - *(lut_ptr + lut_entry);
}
