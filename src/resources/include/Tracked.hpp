#pragma once

template<typename T>
class Tracked
{
public:

    Tracked() : value{} {}
    explicit Tracked(T value) : value{value} {}

    T operator*() const
    {
        return value;
    }

    bool operator==(const T& other) const
    {
        return value == other;
    }

    bool operator==(const Tracked<T>& other) const
    {
        return value == other.value;
    }

    Tracked& operator=(T other)
    {
        value = other;
        return *this;
    }

    Tracked operator+(T other) const
    {
        return Tracked(value + other);
    }

    Tracked operator+(const Tracked<T>& other) const
    {
        return operator+(other.value);
    }

    Tracked operator-(T other) const
    {
        return Tracked(value - other);
    }

    Tracked operator-(const Tracked<T>& other) const
    {
        return operator-(other.value);
    }

    Tracked operator*(T other) const
    {
        return Tracked(value * other);
    }

    Tracked operator*(const Tracked<T>& other) const
    {
        return operator*(other.value);
    }

    Tracked operator/(T other) const
    {
        return Tracked(value / other);
    }

    Tracked operator/(const Tracked<T>& other) const
    {
        return operator/(other.value);
    }

    explicit operator T() const
    {
        return value;
    }

private:

    T value;
};
