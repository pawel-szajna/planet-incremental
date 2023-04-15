#pragma once

#include <string>

namespace World
{
/**
 * A Node is the very basic building block of the world.
 */
class Node
{
public:

    Node(std::string comment);
    ~Node();

    std::string comment;
};
} // namespace World
