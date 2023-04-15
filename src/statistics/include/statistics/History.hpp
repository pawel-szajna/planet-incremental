#pragma once

#include <deque>

#include "common/types.hpp"

namespace Statistics
{
template<size_t Limit, typename Number = Common::Number>
class History
{
public:

    using value_type     = Number;
    using container_type = std::deque<value_type>;
    using iterator       = typename container_type::iterator;
    using const_iterator = typename container_type::const_iterator;

    iterator begin() noexcept { return data.begin(); }

    iterator end() noexcept { return data.end(); }

    [[nodiscard]] const_iterator begin() const noexcept { return data.cbegin(); }

    [[nodiscard]] const_iterator end() const noexcept { return data.cend(); }

    [[nodiscard]] bool empty() const noexcept { return data.empty(); }

    [[nodiscard]] size_t size() const noexcept { return data.size(); }

    [[nodiscard]] constexpr size_t limit() const noexcept { return Limit; }

    void emplace(value_type value)
    {
        if (size() >= Limit)
        {
            data.pop_front();
        }
        data.emplace_back(value);
    }

private:

    container_type data{};
};
} // namespace Statistics
