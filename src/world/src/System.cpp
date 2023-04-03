#include "System.hpp"

namespace World
{
System::System()
{
    planets.emplace_back(Planet{});
}

System::~System() = default;
}