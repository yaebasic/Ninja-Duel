#include "input.h"

#include <keypadc.h>

void Input::poll()
{
    // kb_Data[] maps to fixed keypad register offsets

    m_keys[KEY_UP]    = (kb_Data[7] & kb_Up);
    m_keys[KEY_DOWN]  = (kb_Data[7] & kb_Down);
    m_keys[KEY_LEFT]  = (kb_Data[7] & kb_Left);
    m_keys[KEY_RIGHT] = (kb_Data[7] & kb_Right);
    m_keys[KEY_2ND]   = (kb_Data[1] & kb_2nd);
    m_keys[KEY_ALPHA] = (kb_Data[2] & kb_Alpha);
    m_keys[KEY_MODE]  = (kb_Data[1] & kb_Mode);
    m_keys[KEY_XT0N]  = (kb_Data[3] & kb_GraphVar);
    m_keys[KEY_CLEAR] = (kb_Data[6] & kb_Clear);
}

bool Input::getKeyState(enum Keys key) const
{
    return m_keys[key];
}
