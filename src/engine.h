#pragma once

#include "images.h"
#include "input.h"

class Engine
{

public:

    // runs game container
    void run();

private:

    // game loop logic
    bool step();

    // game loop rendeirng
    void draw();

    // checks if user has invoked quit
    bool quit();

    // image (sprites) handler
    Images images;

    // input handler
    Input input;
    
};