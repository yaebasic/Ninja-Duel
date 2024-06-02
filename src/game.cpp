#include "game.h"
#include "engine.h"

#include <graphx.h>
#include <keypadc.h>

void Game::start()
{
    Engine engine;

    begin();

    engine.run();

    end();
}

void Game::begin()
{
    // setup graphics routine
    gfx_Begin();
    gfx_SetDrawBuffer();

    // set system to continuously scan keyboard
    // as opposed to manually calling kb_Scan() every game loop
    kb_SetMode(MODE_3_CONTINUOUS);
}

void Game::end()
{
    // end graphics routine
    gfx_End();
}
