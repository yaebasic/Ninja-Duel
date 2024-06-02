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

    // avoid a separate #define
    KEY_CNT
};

class Input
{

public:

    void poll();

    bool getKey(enum Keys key);

private:

    bool keys[KEY_CNT] = { false };

};