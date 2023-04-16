#pragma once

#include <string>

namespace World
{
/**
 * @class Node
 * @brief A Node is the very basic building block of the world.
 *
 * Every node is represented as a cube in the game world. The node might have various properties,
 * however as of now it can only hold a text value.
 */
class Node
{
public:

    Node(std::string comment);
    ~Node();

    std::string comment;
};
} // namespace World
