#pragma once

#include "world/Planet.hpp"

#include <vector>

namespace World
{
/**
 * @class System
 * @brief A planetary system, consisting of a star along with planets.
 */
class System
{
public:

    System();
    ~System();

    double starX{0.0}, starY{0.0}, starZ{0.0};
    std::vector<Planet> planets;

private:
};
} // namespace World
