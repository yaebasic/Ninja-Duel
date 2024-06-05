#pragma once

#include "defines.h"

enum Keys
{
    KEY_UP,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT,
    KEY_2ND,
    KEY_ALPHA,
    KEY_MODE,
    KEY_XT0N,
    KEY_CLEAR,

    KEY_COUNT
};

class Input
{

public:

    void poll();

    bool getKeyState(enum Keys key) const;

private:

    // stores key states as either on (is pressed) or off (is not pressed)
    bool m_keys[KEY_COUNT] = { false };

};