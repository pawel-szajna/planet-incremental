#pragma once

#include <memory>

namespace World
{
class Universe;
}

namespace Game
{
class Game
{
#if defined(PLATFORM_WEB)
    friend void callLoop(void* gamePtr);
#endif

public:

    Game();
    ~Game();

    void start();

private:

    void loop();
    void executeLoop();

    std::unique_ptr<World::Universe> universe{};
};
} // namespace Game
