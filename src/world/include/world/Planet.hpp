#pragma once

#include "Node.hpp"

#include <array>
#include <map>
#include <string>
#include <vector>

namespace World
{
constexpr auto CHUNK_SIZE = 8;

class Chunk
{
public:

    Chunk() {}

    ~Chunk() {}

    [[nodiscard]] Node& at(int x, int y, int z) { return nodes.at(x + y * CHUNK_SIZE).at(z); }

    [[nodiscard]] const Node& at(int x, int y, int z) const { return nodes.at(x + y * CHUNK_SIZE).at(z); }

private:

    std::array<std::vector<Node>, CHUNK_SIZE * CHUNK_SIZE> nodes{};
};

/**
 * @class ChunkedSpace
 * @brief Helper class to access elements stored within chunks.
 *
 * Every Node in the game Planet's space exists in exactly one Chunk. This ChunkedSpace helper class
 * allows easy access to the Node with given coordinates and handles the calculation of which Chunk
 * stores the Node.
 */
class ChunkedSpace
{
public:

    using ChunkCoordinates = std::pair<int, int>;

    [[nodiscard]] Node& at(int x, int y, int z)
    {
        return chunks.at(getCoordinates(x, y)).at(x % CHUNK_SIZE, y % CHUNK_SIZE, z);
    }

    [[nodiscard]] const Node& at(int x, int y, int z) const
    {
        return chunks.at(getCoordinates(x, y)).at(x % CHUNK_SIZE, y % CHUNK_SIZE, z);
    }

private:

    static ChunkCoordinates getCoordinates(int x, int y) noexcept
    {
        return std::make_pair(x / CHUNK_SIZE, y / CHUNK_SIZE);
    }

    std::map<ChunkCoordinates, Chunk> chunks{};
};

/**
 * @class Planet
 * @brief A Planet is a collection of Nodes.
 */
class Planet
{
public:

    Planet();
    ~Planet();

    std::string name;
    double distance;

    std::map<std::pair<int, int>, std::vector<Node>> nodes;
    ChunkedSpace space;

private:
};
} // namespace World
