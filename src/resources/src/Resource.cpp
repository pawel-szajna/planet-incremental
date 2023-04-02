#include "Resource.hpp"

Resource::Resource(std::string name) :
    name{std::move(name)}
{}

Resource::~Resource() = default;

Resource::operator Number::value_type() const noexcept
{
    return value.operator Number::value_type();
}

Resource::Number& Resource::operator*() noexcept
{
    return value;
}

const Resource::Number& Resource::operator*() const noexcept
{
    return value;
}
