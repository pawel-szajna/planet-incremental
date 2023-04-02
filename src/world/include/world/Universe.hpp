#pragma once

#include "world/System.hpp"

namespace World
{
/**
 * Universe is endless and contains many planetary systems.
 */
class Universe
{
public:

    Universe();
    ~Universe();

    System system;
};
}
