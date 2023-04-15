#pragma once

#include <string>

namespace Statistics
{
class Achievement
{
public:

    virtual ~Achievement() = default;

    virtual std::string name()        = 0;
    virtual std::string description() = 0;

    virtual void verify()   = 0;
    virtual bool unlocked() = 0;

    virtual void render() = 0;
};
} // namespace Statistics
