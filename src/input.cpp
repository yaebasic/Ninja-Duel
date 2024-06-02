#include "input.h"

#include <keypadc.h>

void Input::poll()
{
    // kb_Data[] maps to keypad register offsets
    // register map can be found in toolchain wiki

    keys[KEY_UP]    = (kb_Data[7] & kb_Up);
    keys[KEY_DOWN]  = (kb_Data[7] & kb_Down);
    keys[KEY_LEFT]  = (kb_Data[7] & kb_Left);
    keys[KEY_RIGHT] = (kb_Data[7] & kb_Right);
    keys[KEY_2ND]   = (kb_Data[1] & kb_2nd);
    keys[KEY_ALPHA] = (kb_Data[2] & kb_Alpha);
    keys[KEY_MODE]  = (kb_Data[1] & kb_Mode);
    keys[KEY_XT0N]  = (kb_Data[3] & kb_GraphVar);
    keys[KEY_CLEAR] = (kb_Data[6] & kb_Clear);
}

bool Input::getKey(enum Keys key)
{
    return keys[key];
}
