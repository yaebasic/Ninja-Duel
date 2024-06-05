#include "game.h"
#include "engine.h"

#include <graphx.h>
#include <keypadc.h>

Game::Game()
{
    gfx_Begin();
    gfx_SetDrawBuffer();

    kb_SetMode(MODE_3_CONTINUOUS);
}

Game::~Game()
{
    gfx_End();
}

void Game::start()
{
    Engine engine;

    engine.run();
}
