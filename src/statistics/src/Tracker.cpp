#include "Tracker.hpp"

namespace
{
template<class MaybePair>
concept is_pair = requires(MaybePair pair) {
    std::tuple_size_v<MaybePair> == 2;
    std::get<0>(pair);
    std::get<1>(pair);
};

template<size_t Resolution, typename HistoryType>
requires is_pair<HistoryType>
void update(HistoryType& historyData, Common::Number value)
{
    auto& [history, ticks] = historyData;

    if (ticks == 0)
    {
        history.emplace(value);
        ticks = Resolution;
    }

    --ticks;
}
} // namespace

namespace Statistics
{
Tracker::Tracker() = default;

Tracker::~Tracker() = default;

void Tracker::tick(Common::Number value)
{
    update<SHORT_HISTORY_RESOLUTION>(shortHistory, value);
    update<MEDIUM_HISTORY_RESOLUTION>(mediumHistory, value);
    update<LONG_HISTORY_RESOLUTION>(longHistory, value);
    update<VERY_LONG_HISTORY_RESOLUTION>(veryLongHistory, value);
}

const Tracker::ShortHistory& Tracker::getShortHistory() const
{
    return shortHistory.first;
}

const Tracker::MediumHistory& Tracker::getMediumHistory() const
{
    return mediumHistory.first;
}

const Tracker::LongHistory& Tracker::getLongHistory() const
{
    return longHistory.first;
}

const Tracker::VeryLongHistory& Tracker::getVeryLongHistory() const
{
    return veryLongHistory.first;
}
} // namespace Statistics
