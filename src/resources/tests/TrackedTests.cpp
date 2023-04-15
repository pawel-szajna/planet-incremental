#include "Tracked.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace ::testing;

template<typename T>
class TrackedBasicTests : public Test
{
protected:

    template<typename... Args>
    auto make_sut(Args&&... args)
    {
        return Tracked<T>(std::forward<Args>(args)...);
    }
};

using TrackedBasicTestsTypes = Types<int, unsigned, double>;
TYPED_TEST_SUITE(TrackedBasicTests, TrackedBasicTestsTypes);

TYPED_TEST(TrackedBasicTests, shouldCarryTypeDefaultValueOnConstruction)
{
    auto sut = this->make_sut();
    ASSERT_EQ(*sut, TypeParam{});
    ASSERT_TRUE(sut == TypeParam{});
}

TYPED_TEST(TrackedBasicTests, shouldAssignAndReturnValueOfUnderlyingType)
{
    auto sut = this->make_sut(4);
    ASSERT_EQ(*sut, TypeParam{4});
    ASSERT_TRUE(sut == TypeParam{4});

    sut = TypeParam{5};
    ASSERT_NE(*sut, TypeParam{4});
    ASSERT_FALSE(sut == TypeParam{4});
    ASSERT_EQ(*sut, TypeParam{5});
    ASSERT_TRUE(sut == TypeParam{5});

    TypeParam value{};
    value = (TypeParam)sut;
    ASSERT_EQ(value, TypeParam{5});
}

TYPED_TEST(TrackedBasicTests, shouldCompareMultipleTrackedValues)
{
    auto sut1 = this->make_sut(2);
    auto sut2 = this->make_sut(3);
    auto sut3 = this->make_sut(3);

    ASSERT_NE(sut1, sut2);
    ASSERT_NE(sut1, sut3);
    ASSERT_EQ(sut2, sut3);

    sut3 = sut1;

    ASSERT_NE(sut1, sut2);
    ASSERT_EQ(sut1, sut3);
    ASSERT_NE(sut2, sut3);
}

TYPED_TEST(TrackedBasicTests, shouldPerformBasicOperations)
{
    TypeParam valueA = 2;
    TypeParam valueB = 3;
    auto sutA        = this->make_sut(valueA);
    auto sutB        = this->make_sut(valueB);

    ASSERT_EQ(valueA + valueB, sutA + sutB);
    ASSERT_EQ(valueA + valueB, sutB + sutA);
    ASSERT_EQ(valueA + valueB, sutA + valueB);

    ASSERT_EQ(valueB - valueA, sutB - sutA);
    ASSERT_EQ(valueB - valueA, sutB - valueA);

    ASSERT_EQ(valueA * valueB, sutA * sutB);
    ASSERT_EQ(valueA * valueB, sutA * valueB);

    ASSERT_EQ(valueA / valueB, sutA / sutB);
    ASSERT_EQ(valueA / valueB, sutA / valueB);
}

TYPED_TEST(TrackedBasicTests, shouldIterateOverHistory)
{
    auto sut = this->make_sut(0);
    sut += 1;
    sut *= 2;
    sut -= 2;

    ASSERT_THAT(sut, ElementsAre(0, 1, 2, 0));
}

TYPED_TEST(TrackedBasicTests, historiesShouldBeIndependent)
{
    auto sut = this->make_sut(10);
    sut *= 2;

    ASSERT_THAT(sut, ElementsAre(10, 20));

    auto otherSut = sut + TypeParam{5};
    sut += 10;

    ASSERT_THAT(sut, ElementsAre(10, 20, 30));
    ASSERT_THAT(otherSut, ElementsAre(10, 20, 25));
}
