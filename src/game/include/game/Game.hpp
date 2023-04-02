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
public:

    Game();
    ~Game();

    void start();

    std::unique_ptr<World::Universe> universe{};
};
}
