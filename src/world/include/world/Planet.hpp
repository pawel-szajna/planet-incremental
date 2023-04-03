#pragma once

#include "Node.hpp"

#include <map>
#include <string>
#include <vector>

namespace World
{
/**
 * A Planet is a collection of Nodes.
 */
class Planet
{
public:

    Planet();
    ~Planet();

    std::string name;
    double distance;

    std::map<std::pair<int, int>, std::vector<Node>> nodes;

private:
};
}