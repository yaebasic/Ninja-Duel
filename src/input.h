#pragma once

#include "defines.h"

// enumeration used to access individual keys
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

    // avoid a separate #define
    KEY_COUNT
};

class Input
{

public:

    // updates key states as either on (is pressed) or off (is not pressed)
    void poll();

    // given `key` parameter
    // \returns `0` if not pressed and `1` if pressed
    bool getKey(enum Keys key) const;

private:

    // stores key states as either on (is pressed) or off (is not pressed)
    bool m_keys[KEY_COUNT] = { false };

};