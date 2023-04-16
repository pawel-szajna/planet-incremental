#include "Elements.hpp"

namespace Resources
{
Elements::Elements()
    : elements{Element{std::to_underlying(Type::Iron), "Iron", {141, 162, 196}}}
{
}

Elements::~Elements() = default;

const Element& Elements::get(Type type) const
{
    auto requestedId    = std::to_underlying(type);
    const auto& element = elements.at(requestedId);
    if (element.id == requestedId)
    {
        return element;
    }
    return *std::find_if(elements.begin(),
                         elements.end(),
                         [requestedId](const auto& e) { return e.id == requestedId; });
}
} // namespace Resources
