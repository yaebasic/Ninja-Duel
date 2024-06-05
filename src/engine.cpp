#include "defines.h"
#include "engine.h"

#include <graphx.h>

void Engine::run()
{
    while(step())
    {
        draw();
        limitFps();
    }    
}

bool Engine::step() 
{
    m_input.poll();
    m_animation.update();
    
    return !quit();
}

void Engine::draw() const
{
    gfx_FillScreen(COLOR_WHITE);

    gfx_RLETSprite_NoClip(m_images.getSprite(m_animation.getAnimationIndex()),
        100, 100);
    
    gfx_SwapDraw();
}

bool Engine::quit() const
{
    return m_input.getKeyState(KEY_CLEAR);
}

void Engine::limitFps()
{
    while(clock() - m_last_clock < CLOCKS_PER_SEC / TARGET_FRAMERATE);
    m_last_clock = clock();
}
