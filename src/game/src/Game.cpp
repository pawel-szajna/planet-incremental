#include "Game.hpp"

#include "common/logger.hpp"
#include "world/Universe.hpp"

#include <spdlog/fmt/bundled/printf.h>

// clang-format off
// Those headers must not be sorted alphabetically.
#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>
#include <dark/dark.h>
#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif
// clang-format on

namespace Game
{
#if defined(PLATFORM_WEB)
void callLoop(void* gamePtr)
{
    static_cast<Game*>(gamePtr)->loop();
}

extern "C"
{
    void updateSize(int width, int height)
    {
        SetWindowSize(width, height);
    }
}
#endif

void raylibLog(int severity, const char* text, va_list args)
{
    static char formatted[256]; // MAX_TRACELOG_MSG_LENGTH
    vsprintf(formatted, text, args);
    switch (severity)
    {
    case LOG_DEBUG:
        spdlog::debug("[raylib] {}", formatted);
        return;
    case LOG_WARNING:
        spdlog::warn("[raylib] {}", formatted);
        return;
    case LOG_ERROR:
        spdlog::error("[raylib] {}", formatted);
        return;
    case LOG_FATAL:
        spdlog::critical("[raylib] {}", formatted);
        return;
    case LOG_INFO:
    default:
        spdlog::info("[raylib] {}", formatted);
        return;
    }
}

Camera3D camera{};

Game::Game()
{
    logDebug("Constructing main structures");
    SetTraceLogCallback(raylibLog);
    universe = std::make_unique<World::Universe>();
}

Game::~Game() = default;

void Game::start()
{
    logDebug("Starting the game");
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(1024, 768, "planet incremental");
    SetWindowMinSize(640, 480);
    SetTargetFPS(60);
    GuiLoadStyleDark();
    camera.position   = {10.0f, 10.0f, 10.0f};
    camera.target     = {0.0f, 0.0f, 0.0f};
    camera.up         = {0.0f, 0.0f, 1.0f};
    camera.fovy       = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    executeLoop();
    CloseWindow();
}

void Game::loop()
{
    BeginDrawing();
    ClearBackground(BLACK);
    DrawCircleV(Vector2{320, 240}, 15, RED);

    // camera.position.x += 0.01f;
    // camera.target.x += 0.01f;

    auto collided = false;
    auto mouse    = GetMousePosition();
    std::string ccaption{};
    BeginMode3D(camera);
    auto ray = GetMouseRay(GetMousePosition(), camera);
    for (auto& [coords, column] : universe->system.planets.front().nodes)
    {
        auto [nodeX, nodeY] = coords;
        auto nodeZ          = 0.5f;
        for (const auto& node : column)
        {
            nodeZ += 1.0;

            Color wire = LIME;
            if (GetRayCollisionBox(
                    ray,
                    {{nodeX + 0.0f, nodeY + 0.0f, nodeZ - 0.5f}, {nodeX + 1.0f, nodeY + 1.0f, nodeZ + 0.5f}})
                    .hit)
            {
                wire     = GREEN;
                mouse    = GetMousePosition();
                collided = true;
                ccaption = node.comment;
            }
            DrawCube({nodeX + 0.5f, nodeY + 0.5f, nodeZ}, 1.0, 1.0, 1.0, RED);
            DrawCubeWires({nodeX + 0.5f, nodeY + 0.5f, nodeZ}, 1.0, 1.0, 1.0, wire);
        }
    }
    EndMode3D();

    if (collided)
    {
        GuiFade(0.9f);
        GuiStatusBar({mouse.x + 16, mouse.y + 16, 100, 24}, ccaption.c_str());
        GuiFade(1.0f);
    }

    std::string caption = "Time: " + std::to_string(GetTime());
    GuiStatusBar({0, 0, (float)GetScreenWidth(), 24}, caption.c_str());
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
} // namespace Game
