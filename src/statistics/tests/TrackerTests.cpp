#include "Tracker.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <numeric>

using namespace ::testing;

namespace
{
constexpr auto TicksCount              = 10'000;
constexpr Common::Number ResourceCount = 2137;
} // namespace

namespace Statistics
{
struct TrackerTests : public Test
{
    Tracker sut{};
};

TEST_F(TrackerTests, shouldHaveEmptyHistoryOnCreation)
{
    EXPECT_TRUE(sut.getShortHistory().empty());
    EXPECT_TRUE(sut.getMediumHistory().empty());
    EXPECT_TRUE(sut.getLongHistory().empty());
    EXPECT_TRUE(sut.getVeryLongHistory().empty());
}

TEST_F(TrackerTests, shouldLogFirstTickEverywhere)
{
    sut.tick(ResourceCount);
    EXPECT_THAT(sut.getShortHistory(), ElementsAre(ResourceCount));
    EXPECT_THAT(sut.getMediumHistory(), ElementsAre(ResourceCount));
    EXPECT_THAT(sut.getLongHistory(), ElementsAre(ResourceCount));
    EXPECT_THAT(sut.getVeryLongHistory(), ElementsAre(ResourceCount));
}

// Yes, this one is ugly
TEST_F(TrackerTests, shouldKeepHistoryInIntervals)
{
    for (int i = 0; i < TicksCount; ++i)
    {
        sut.tick(i);
    }

    std::vector<Common::Number> shorts(300);
    std::iota(shorts.begin(), shorts.end(), 9700);

    std::vector<Common::Number> mediums(200);
    std::iota(mediums.begin(), mediums.end(), 467);
    std::transform(mediums.begin(),
                   mediums.end(),
                   mediums.begin(),
                   [](auto& n)
                   {
                       n *= 15;
                       return n;
                   });

    std::vector<Common::Number> longs(34);
    std::iota(longs.begin(), longs.end(), 0);
    std::transform(longs.begin(),
                   longs.end(),
                   longs.begin(),
                   [](auto n)
                   {
                       n *= 300;
                       return n;
                   });

    std::vector<Common::Number> veryLongs{0, 6000};

    EXPECT_THAT(sut.getShortHistory(), ElementsAreArray(shorts));
    EXPECT_THAT(sut.getMediumHistory(), ElementsAreArray(mediums));
    EXPECT_THAT(sut.getLongHistory(), ElementsAreArray(longs));
    EXPECT_THAT(sut.getVeryLongHistory(), ElementsAreArray(veryLongs));
}
} // namespace Statistics
