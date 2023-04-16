#pragma once

#include <memory>

namespace World
{
class Universe;
}

namespace Front
{
class Front
{
#if defined(PLATFORM_WEB)
    friend void callLoop(void* gamePtr);
#endif

public:

    Front();
    ~Front();

    void start();

private:

    void loop();
    void executeLoop();

    std::unique_ptr<World::Universe> universe{};
};
} // namespace Front
