#include "count_answers_in_group.hpp"
#include "gtest/gtest.h"
#include <string>
#include <tuple>

class CountUniqueAnswersInGroupFixture
    : public ::testing::TestWithParam<std::tuple<std::string, int>> {
};

TEST_P(CountUniqueAnswersInGroupFixture, CountUniqueAnswersReturnsCorrectNumber)
{
    std::string const groupInput = std::get<0>(GetParam());
    int expectedResult = std::get<1>(GetParam());

    EXPECT_EQ(countUniqueAnswersInGroup(groupInput), expectedResult);
}

INSTANTIATE_TEST_SUITE_P(CountUniqueAnswersInGroup, CountUniqueAnswersInGroupFixture,
    ::testing::Values(std::make_tuple("a", 1), std::make_tuple("ab", 2),
        std::make_tuple("ab\nc", 3), std::make_tuple("ab\nac", 3)));

class CountCommonAnswersInGroupFixture
    : public ::testing::TestWithParam<std::tuple<std::string, int>> {
};

TEST_P(CountCommonAnswersInGroupFixture, CountUniqueAnswersReturnsCorrectNumber)
{
    std::string const groupInput = std::get<0>(GetParam());
    int expectedResult = std::get<1>(GetParam());

    EXPECT_EQ(countCommonAnswersInGroup(groupInput), expectedResult);
}

INSTANTIATE_TEST_SUITE_P(CountCommonAnswersInGroup, CountCommonAnswersInGroupFixture,
    ::testing::Values(std::make_tuple("a", 1), std::make_tuple("ab", 2),
        std::make_tuple("ab\nc", 0), std::make_tuple("ab\nac", 1),
        std::make_tuple("abc\nabc\nabd", 2)));
