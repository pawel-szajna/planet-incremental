#include "common/logger.hpp"
#include "game/Game.hpp"

#if not defined(DEBUG_MODE)
    #include <stdexcept>
#endif

int main()
#if not defined(DEBUG_MODE)
try
#endif
{
#if defined(DEBUG_MODE)
    spdlog::set_level(spdlog::level::debug);
#endif
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
