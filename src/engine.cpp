#include "engine.h"

#include <graphx.h>

void Engine::run()
{
    while(step())
    {
        draw();
    }
}

bool Engine::quit()
{
    return input.getKey(KEY_CLEAR);
}

bool Engine::step()
{
    input.poll();
    
    // check if user invoked quit
    return !quit();
}

void Engine::draw()
{
    gfx_SwapDraw();
}
