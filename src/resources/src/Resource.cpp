#include "Resource.hpp"

Resource::Resource(std::string name) :
    name{std::move(name)}
{}

Resource::~Resource() = default;

Resource::operator Number() const noexcept
{
    return operator*();
}

Resource::Number& Resource::operator*() noexcept
{
    return value;
}

const Resource::Number& Resource::operator*() const noexcept
{
    return value;
}
