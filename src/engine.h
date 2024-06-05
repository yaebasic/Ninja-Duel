#pragma once

#include "animation.h"
#include "images.h"
#include "input.h"

#include <time.h>

class Engine
{

public:

    void run();

private:

    bool step();
    void draw() const;

    bool quit() const;
    void limitFps();

    Animation m_animation;
    Images m_images;
    Input m_input;

    // frametime tracker
    clock_t m_last_clock = clock();
    
};