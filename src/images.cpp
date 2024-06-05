#include "defines.h"
#include "images.h"

#include <fileioc.h>
#include <graphx.h>

// Image data is stored in an appvar. A LookUp Table (LUT) is embedded at start
// of file. Each entry is 3-bytes and is structured as below:
//
//  `Entry 0`: Number of entries in LUT
//  `Entry 1`: Byte offset to first entry (points to palette data)
//  `Entry 2`: Byte offset to second entry (points to data of first sprite)
//  ...
//  `Entry N`: Byte offset to last entry (points to data of last sprite)
//
enum LUTOffsets
{
    LUT_ENTRY_CNT,
    LUT_OFFSET_PALETTE,
    LUT_OFFSET_SPRITES
};

Images::Images()
{
    m_appvar = ti_Open(IMG_APPVAR_NAME, "r");

    // points lut_ptr to start of lut table (i.e., start of appvar)
    m_lut_ptr = (LUT*)ti_GetDataPtr(m_appvar);

    loadPalette();
    loadSprites();

    ti_Close(m_appvar);
}

const gfx_rletsprite_t *Images::getSprite(u8 index) const
{
    return m_images[index];
}

void Images::loadPalette() const
{
    const u24 pal_size = getLutEntrySize(LUT_OFFSET_PALETTE);
    const u8 *const pal_ptr = getLutEntryPtr(LUT_OFFSET_PALETTE);

    gfx_SetPalette(pal_ptr, pal_size, 0);
}

void Images::loadSprites()
{
    // retrieve pointer to each sprite and stores it into images[]
    for (u8 i = 0; i < SPRITE_COUNT; ++i)
    {
        const u8 *const spr_ptr = getLutEntryPtr(LUT_OFFSET_SPRITES + i);
        m_images[i] = (gfx_rletsprite_t*)spr_ptr;
    }
}

const u8 *Images::getLutEntryPtr(u8 lut_entry) const
{
    // LUT entries = 3-bytes, offset values = 1-byte
    // --> type conversion needed to determine offset's address
    return (u8*)m_lut_ptr + *(m_lut_ptr + lut_entry);
}

LUT Images::getLutEntrySize(u8 lut_entry) const
{
    // m_lut_ptr dereferences to entry count
    const u8 max_entry = *(u8*)m_lut_ptr;

    if (lut_entry == max_entry)
    {
        // find size of entire appvar and subtract offset of current entry
        return ti_GetSize(m_appvar) - *(m_lut_ptr + lut_entry);
    }

    // find offset of next entry and subtract current offset
    return *(m_lut_ptr + lut_entry + 1) - *(m_lut_ptr + lut_entry);
}
