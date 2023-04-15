#include "Node.hpp"

namespace World
{
Node::Node(std::string comment)
    : comment{std::move(comment)}
{
}

Node::~Node() = default;
} // namespace World
