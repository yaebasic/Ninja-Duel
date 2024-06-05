#pragma once

#include "animation.h"
#include "images.h"
#include "input.h"

#include <time.h>

class Engine
{

public:

    // runs game container
    void run();

private:

    // game loop logic
    bool step();

    // game loop rendeirng
    void draw() const;

    // checks if user has invoked quit
    bool quit() const;

    // framerate limiter
    void limitFps();

    // animation handler
    Animation m_animation;

    // image (sprites) handler
    Images m_images;

    // input handler
    Input m_input;

    clock_t m_last_clock = clock();
    
};