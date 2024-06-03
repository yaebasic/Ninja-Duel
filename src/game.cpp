#include "game.h"
#include "engine.h"

#include <graphx.h>
#include <keypadc.h>

#include <debug.h>

void Game::start()
{
    Engine engine;

    init();

    engine.run();

    clean();

}

void Game::init()
{
    // setup graphics routine
    gfx_Begin();
    gfx_SetDrawBuffer();

    // set system to continuously scan keyboard
    // as opposed to manually calling kb_Scan() every game loop
    kb_SetMode(MODE_3_CONTINUOUS);
}

void Game::clean()
{
    // end graphics routine
    gfx_End();
}
