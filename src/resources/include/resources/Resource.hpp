#pragma once

#include "Tracked.hpp"

#include <string>

class Resource
{
    using Number = double;

    explicit Resource(std::string name);
    ~Resource();

    Number& operator*() noexcept;
    const Number& operator*() const noexcept;
    operator Number() const noexcept; // NOLINT(google-explicit-constructor)

    const std::string& getName() { return name; }

private:

    std::string name;
    Number value;
};
