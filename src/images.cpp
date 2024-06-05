#include "images.h"

#include <fileioc.h>
#include <graphx.h>

// Image data is stored in an appvar. A LookUp Table (LUT) is embedded at the
// start of the file. Each entry is 3-bytes and is structured as below:
//
//  `Entry 0`: Number of entries in the LUT
//  `Entry 1`: Byte offset to first entry (points to the palette data)
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

Images::Images()
{
    m_appvar = ti_Open(APPVAR_NAME, "r");

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
    const u24 pal_size = getDataSize(LUT_OFFSET_PALETTE);
    const u8 *const pal_ptr = getDataPtr(LUT_OFFSET_PALETTE);

    gfx_SetPalette(pal_ptr, pal_size, 0);
}

void Images::loadSprites()
{
    for (u8 i = 0; i < SPRITE_COUNT; ++i)
    {
        // retrieve the pointer to the sprite
        const u8 *const spr_ptr = getDataPtr(LUT_OFFSET_SPRITES + i);

        // and store the pointer into the index
        m_images[i] = (gfx_rletsprite_t*)spr_ptr;
    }
}

const u8 *Images::getDataPtr(u8 lut_entry) const
{
    // (3-bytes) LUT entries    ,i.e.,  (u8*)m_lut_ptr
    // (1-byte)  offset values  ,i.e.,  *(m_lut_ptr + lut_entry)
    //
    //      --> type conversion needed to determine offset's pointer location
    //
    return (u8*)m_lut_ptr + *(m_lut_ptr + lut_entry);
}

LUT Images::getDataSize(u8 lut_entry) const
{
    // m_lut_ptr dereferences to entry count (see explanation at top of file)
    const u8 max_entry = *(u8*)m_lut_ptr;

    // if last entry in table, find size of entire appvar and subtract offset
    // of current entry to determine data size
    if (lut_entry == max_entry)
    {
        return ti_GetSize(m_appvar) - *(m_lut_ptr + lut_entry);
    }

    // otherwise, find offset of next entry and subtract current offset to
    // determine data size
    return *(m_lut_ptr + lut_entry + 1) - *(m_lut_ptr + lut_entry);
}
