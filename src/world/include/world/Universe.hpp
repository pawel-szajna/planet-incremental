#pragma once

#include "world/System.hpp"

namespace World
{
/**
 * @class Universe
 * @brief Endless space filled with planetary systems.
 *
 * The Universe is currently the biggest entity in the game world. Ambitious enough to want to be
 * infinite, in reality only contains a single star system. One day, perhaps...
 */
class Universe
{
public:

    Universe();
    ~Universe();

    System system;
};
} // namespace World
