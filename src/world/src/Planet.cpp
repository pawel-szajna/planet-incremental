#include "Planet.hpp"

namespace World
{
Planet::Planet()
{
    nodes[{0, 0}] = {Node("nothing")};
    nodes[{0, 1}] = {Node("maybe something")};
    nodes[{1, 0}] = {Node("whatever")};
    nodes[{1, 1}] = {Node("low"), Node("high")};
}

Planet::~Planet() = default;
}