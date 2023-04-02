#pragma once

#include <string>

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

private:
};
}