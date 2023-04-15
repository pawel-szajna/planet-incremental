#pragma once

#include <array>
#include <deque>
#include <utility>

#include "common/constants.hpp"
#include "common/types.hpp"
#include "History.hpp"

namespace Statistics
{
class Tracker
{
public:

    template<Common::Size Length>
    using HistoryData = std::pair<History<Length>, Common::Size>;

    constexpr static auto SHORT_HISTORY_TIME{30};
    constexpr static auto SHORT_HISTORY_RESOLUTION{1};
    constexpr static auto MEDIUM_HISTORY_TIME{300};
    constexpr static auto MEDIUM_HISTORY_RESOLUTION{15};
    constexpr static auto LONG_HISTORY_TIME{3600};
    constexpr static auto LONG_HISTORY_RESOLUTION{Common::TICKS_PER_SECOND * 30};
    constexpr static auto VERY_LONG_HISTORY_TIME{3600 * 24};
    constexpr static auto VERY_LONG_HISTORY_RESOLUTION{Common::TICKS_PER_SECOND * 600};

    constexpr static auto SHORT_HISTORY_SIZE{SHORT_HISTORY_TIME * Common::TICKS_PER_SECOND / SHORT_HISTORY_RESOLUTION};
    constexpr static auto MEDIUM_HISTORY_SIZE{MEDIUM_HISTORY_TIME * Common::TICKS_PER_SECOND /
                                              MEDIUM_HISTORY_RESOLUTION};
    constexpr static auto LONG_HISTORY_SIZE{LONG_HISTORY_TIME * Common::TICKS_PER_SECOND / LONG_HISTORY_RESOLUTION};
    constexpr static auto VERY_LONG_HISTORY_SIZE{VERY_LONG_HISTORY_TIME * Common::TICKS_PER_SECOND /
                                                 VERY_LONG_HISTORY_RESOLUTION};

    using ShortHistoryData    = HistoryData<SHORT_HISTORY_SIZE>;
    using MediumHistoryData   = HistoryData<MEDIUM_HISTORY_SIZE>;
    using LongHistoryData     = HistoryData<LONG_HISTORY_SIZE>;
    using VeryLongHistoryData = HistoryData<VERY_LONG_HISTORY_SIZE>;

    using ShortHistory    = ShortHistoryData::first_type;
    using MediumHistory   = MediumHistoryData::first_type;
    using LongHistory     = LongHistoryData::first_type;
    using VeryLongHistory = VeryLongHistoryData::first_type;

    Tracker();
    ~Tracker();

    void tick(Common::Number value);

    [[nodiscard]] const ShortHistory& getShortHistory() const;
    [[nodiscard]] const MediumHistory& getMediumHistory() const;
    [[nodiscard]] const LongHistory& getLongHistory() const;
    [[nodiscard]] const VeryLongHistory& getVeryLongHistory() const;

private:

    ShortHistoryData shortHistory;
    MediumHistoryData mediumHistory;
    LongHistoryData longHistory;
    VeryLongHistoryData veryLongHistory;
};
} // namespace Statistics
