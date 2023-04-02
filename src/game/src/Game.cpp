#include "Game.hpp"

#include "world/Universe.hpp"

#include <raylib.h>
#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

namespace Game
{
#if defined(PLATFORM_WEB)
void callLoop(void* gamePtr)
{
    static_cast<Game*>(gamePtr)->loop();
}
#endif

Game::Game()
{
    universe = std::make_unique<World::Universe>();
}

Game::~Game() = default;

void Game::start()
{
    InitWindow(640, 480, "planet incremental");
    SetTargetFPS(60);
    executeLoop();
    CloseWindow();
}

void Game::loop()
{
    BeginDrawing();
    ClearBackground(BLACK);
    DrawCircleV(Vector2{320, 240}, 15, RED);
    EndDrawing();
}

void Game::executeLoop()
{
#if defined(PLATFORM_WEB)
    emscripten_set_main_loop_arg(&callLoop, this, 0, 1);
#else
    while (!WindowShouldClose())
    {
        loop();
    }
#endif
}
}
