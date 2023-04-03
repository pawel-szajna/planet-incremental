#include "History.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace ::testing;

namespace
{
using Number = int;
constexpr size_t Size = 5;
}

namespace Statistics
{
struct HistoryTests : public Test
{
    template<typename ...Args>
    void emplace(Args&&... args)
    {
        (sut.emplace(std::forward<Args>(args)), ...);
    }

    History<Size, Number> sut{};
};

TEST_F(HistoryTests,
       shouldBeEmptyAfterConstruction)
{
    EXPECT_TRUE(sut.empty());
    EXPECT_EQ(sut.size(), 0);
    EXPECT_EQ(sut.begin(), sut.end());
}

TEST_F(HistoryTests,
       shouldContainElement)
{
    constexpr Number element = 2137;

    emplace(element);

    EXPECT_FALSE(sut.empty());
    EXPECT_EQ(sut.size(), 1);
    EXPECT_THAT(sut, ElementsAre(element));
}

TEST_F(HistoryTests,
       shouldRemoveElementsAfterLimitIsReached)
{
    emplace(1, 2, 3, 4, 5);

    EXPECT_EQ(sut.size(), 5);
    EXPECT_THAT(sut, ElementsAre(1, 2, 3, 4, 5));

    emplace(6);

    EXPECT_EQ(sut.size(), 5);
    EXPECT_THAT(sut, ElementsAre(2, 3, 4, 5, 6));
}
}
