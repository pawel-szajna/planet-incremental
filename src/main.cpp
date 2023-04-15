#include "common/logger.hpp"
#include "game/Game.hpp"

#include <stdexcept>

int main()
#if not defined(DEBUG_MODE)
try
#endif
{
    logInfo("Startup of planet-incremental");
    {
        Game::Game game;
        game.start();
    }
    logInfo("Finished");

    return 0;
}
#if not defined(DEBUG_MODE)
catch (const std::exception& e)
{
    logCritical(e.what());
    return 1;
}
#endif
