#include "Game.hpp"

#include "world/Universe.hpp"

#include "raylib.h"

namespace Game
{
Game::Game()
{
    universe = std::make_unique<World::Universe>();
}

Game::~Game() = default;

void Game::start()
{
    InitWindow(640, 480, "planet incremental");
    SetTargetFPS(60);

    while(not WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawCircleV(Vector2{320, 240}, 15, RED);
        EndDrawing();
    }

    CloseWindow();
}
}
