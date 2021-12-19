#include "split_input.hpp"
#include <gtest/gtest.h>

using namespace ::testing;

class SplitInputPolicyTestFixture
    : public ::testing::TestWithParam<std::tuple<std::string, std::string>> {
};

TEST_P(SplitInputPolicyTestFixture, SplitInputReturnsCorrectPolicy)
{
    auto const input_string = std::get<0>(GetParam());
    auto const expected_result = std::get<1>(GetParam());
    auto const [policy_result, _] = split_input(input_string);
    ASSERT_EQ(policy_result, expected_result);
}

INSTANTIATE_TEST_SUITE_P(SplitInputTest, SplitInputPolicyTestFixture,
    ::testing::Values(std::make_tuple("1-1 a: a", "1-1 a"),
        std::make_tuple("1-10 b: abcde", "1-10 b"), std::make_tuple("5-8 x: abcde", "5-8 x")));

class SplitInputPasswordTestFixture
    : public ::testing::TestWithParam<std::tuple<std::string, std::string>> {
};

TEST_P(SplitInputPasswordTestFixture, SplitInputReturnsCorrectPassword)
{
    auto const input_string = std::get<0>(GetParam());
    auto const expected_result = std::get<1>(GetParam());
    auto const [_, password_result] = split_input(input_string);
    ASSERT_EQ(password_result, expected_result);
}
INSTANTIATE_TEST_SUITE_P(SplitInputPasswordTest, SplitInputPasswordTestFixture,
    ::testing::Values(std::make_tuple("1-1 a: a", "a"), std::make_tuple("1-1 a: ab", "ab")));
