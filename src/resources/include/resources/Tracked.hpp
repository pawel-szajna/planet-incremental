#pragma once

#include <vector>

template<typename T, typename C = std::vector<T>>
class Tracked
{
public:

    using value_type     = T;
    using wrapper_type   = Tracked<value_type>;
    using history_type   = C;
    using iterator       = typename history_type::iterator;
    using const_iterator = typename history_type::const_iterator;

    explicit Tracked(value_type value) { update(value); }

    Tracked()
        : Tracked{value_type{}}
    {
    }

    value_type operator*() const noexcept { return value; }

    bool operator==(const value_type& other) const noexcept { return value == other; }

    bool operator==(const wrapper_type& other) const noexcept { return value == other.value; }

    Tracked& operator=(value_type other) { return update(other); } // NOLINT(misc-unconventional-assign-operator)

    Tracked operator+(value_type other) const { return updateClone(value + other); }

    Tracked operator+(const wrapper_type& other) const { return operator+(other.value); }

    Tracked operator-(value_type other) const { return updateClone(value - other); }

    Tracked operator-(const wrapper_type& other) const { return operator-(other.value); }

    Tracked operator*(value_type other) const { return updateClone(value * other); }

    Tracked operator*(const wrapper_type& other) const { return operator*(other.value); }

    Tracked operator/(value_type other) const { return updateClone(value / other); }

    Tracked operator/(const wrapper_type& other) const { return operator/(other.value); }

    Tracked& operator+=(value_type other) { return update(value + other); }

    Tracked& operator+=(const wrapper_type& other) { return operator+=(other.value); }

    Tracked& operator-=(value_type other) { return update(value - other); }

    Tracked& operator-=(const wrapper_type& other) { return operator-=(other.value); }

    Tracked& operator*=(value_type other) { return update(value * other); }

    Tracked& operator*=(const wrapper_type& other) { return operator*=(other.value); }

    Tracked& operator/=(value_type other) { return update(value / other); }

    Tracked& operator/=(const wrapper_type& other) { return operator/=(other.value); }

    operator value_type() const noexcept { return value; } // NOLINT(google-explicit-constructor)

    iterator begin() noexcept { return history.begin(); }

    iterator end() noexcept { return history.end(); }

    const_iterator begin() const noexcept { return history.cbegin(); }

    const_iterator end() const noexcept { return history.cend(); }

private:

    Tracked& update(value_type updated)
    {
        history.push_back(updated);
        value = updated;
        return *this;
    }

    Tracked updateClone(value_type updated) const
    {
        Tracked clone = *this;
        clone.update(updated);
        return clone;
    }

    value_type value;
    history_type history;
};
