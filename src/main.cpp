#include "common/logger.hpp"
#include "front/Front.hpp"

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
        Front::Front gameFrontEnd;
        gameFrontEnd.start();
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
