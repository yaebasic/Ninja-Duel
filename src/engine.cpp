#include "engine.h"

#include <graphx.h>

void Engine::run()
{
    images.extract();

    while(step())
    {
        draw();
    }
}

bool Engine::quit()
{
    // currently set to just pressing clear
    return input.getKey(KEY_CLEAR);
}

bool Engine::step()
{
    input.poll();
    
    return !quit();
}

void Engine::draw()
{
    // example filler
    gfx_FillScreen(0);
    gfx_RLETSprite_NoClip(images.getSprite(2), 100, 100);
    
    gfx_SwapDraw();
}
