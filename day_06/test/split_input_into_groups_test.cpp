#include "split_input_into_groups.hpp"
#include "gtest/gtest.h"
#include <tuple>

class SplitInputIntoGroupsTestFixture
    : public ::testing::TestWithParam<std::tuple<std::string, std::vector<std::string>>> {
};

TEST_P(SplitInputIntoGroupsTestFixture, EmptyStringReturnsEmptyVector)
{
    std::string const input = std::get<0>(GetParam());

    std::vector<std::string> expected_output = std::get<1>(GetParam());

    ASSERT_EQ(splitInputIntoGroups(input), expected_output);
}

INSTANTIATE_TEST_SUITE_P(SplitInputIntoGroupsTest, SplitInputIntoGroupsTestFixture,
    ::testing::Values(std::make_tuple("", std::vector<std::string> {}),
        std::make_tuple("abc", std::vector<std::string> { "abc" }),
        std::make_tuple("def", std::vector<std::string> { "def" }),
        std::make_tuple("abc\n\ndef", std::vector<std::string> { "abc", "def" }),
        std::make_tuple("a\n\nd", std::vector<std::string> { "a", "d" }),
        std::make_tuple("abc\ndef", std::vector<std::string> { "abc\ndef" })));
