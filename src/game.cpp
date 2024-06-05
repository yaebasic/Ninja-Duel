#include "game.h"
#include "engine.h"

#include <graphx.h>
#include <keypadc.h>

Game::Game()
{
    // setup graphics routine
    gfx_Begin();
    gfx_SetDrawBuffer();

    // set system to continuously scan keyboard
    // as opposed to manually invoking scan every game loop
    kb_SetMode(MODE_3_CONTINUOUS);
}

Game::~Game()
{
    // end graphics routine
    gfx_End();
}

void Game::start()
{
    Engine engine;

    engine.run();
}
