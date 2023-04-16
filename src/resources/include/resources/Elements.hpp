#pragma once

#include <string>
#include <tuple>
#include <vector>

namespace Resources
{
struct Element
{
    using Color = std::tuple<int, int, int>;

    int id;
    int atomicNumber;
    float atomicWeight;
    std::string symbol;
    std::string name;
    Color color;
};

class Elements
{
public:

    enum class Type : int
    {
        Iron,
    };

    Elements();
    ~Elements();

    const Element& get(Type type) const;

private:

    std::vector<Element> elements;
};
} // namespace Resources
