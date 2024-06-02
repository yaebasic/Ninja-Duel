#pragma once

#include "input.h"

/**
 * Game Engine Class
*/
class Engine
{

public:

    void run();

    bool quit();

private:

    bool step();
    void draw();

    Input input;

};