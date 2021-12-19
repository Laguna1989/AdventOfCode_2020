#include "is_password_correct.hpp"
#include <gtest/gtest.h>

using namespace ::testing;

class PasswordCorrectTestFixture
    : public ::testing::TestWithParam<std::tuple<std::string, std::string, bool>> {
};

TEST_P(PasswordCorrectTestFixture, IsPasswordCorrect)
{
    auto const policy = std::get<0>(GetParam());
    auto const password = std::get<1>(GetParam());
    auto const expected_result = std::get<2>(GetParam());
    ASSERT_EQ(is_password_correct(policy, password), expected_result);
}

INSTANTIATE_TEST_SUITE_P(PasswordCorrectTestWithOneExpectedLetter, PasswordCorrectTestFixture,
    ::testing::Values(std::make_tuple("1-1 b", "a", false), std::make_tuple("1-1 b", "b", true),
        std::make_tuple("1-1 c", "c", true), std::make_tuple("1-1 d", "d", true),
        std::make_tuple("1-1 d", "ad", false), std::make_tuple("1-1 d", "da", true)));

INSTANTIATE_TEST_SUITE_P(PasswordCorrectTestWithSecondPosExpectedLetter, PasswordCorrectTestFixture,
    ::testing::Values(std::make_tuple("1-2 d", "dd", false), std::make_tuple("1-3 d", "ddd", false),
        std::make_tuple("1-3 d", "dd", true), std::make_tuple("1-4 c", "cccc", false),
        std::make_tuple("1-10 c", "cccccccccc", false),
        std::make_tuple("1-15 f", "fffffffffffffff", false),
        std::make_tuple("1-3 f", "fffffffffffffff", false)));

INSTANTIATE_TEST_SUITE_P(PasswordCorrectTestWithFirstPosExpectedLetter, PasswordCorrectTestFixture,
    ::testing::Values(std::make_tuple("2-2 d", "dd", true), std::make_tuple("2-2 x", "x", false),
        std::make_tuple("4-4 x", "xaxaxaxa", false), std::make_tuple("10-10 x", "xxxxxxxxxx", true),
        std::make_tuple("10-10 x", "xxxxxxxxx", false), std::make_tuple("10-10 x", "x", false)));

INSTANTIATE_TEST_SUITE_P(PasswordCorrectTestWithExpectedLetterRange, PasswordCorrectTestFixture,
    ::testing::Values(std::make_tuple("1-5 a", "a", true), std::make_tuple("1-5 a", "aa", true),
        std::make_tuple("1-5 a", "aaa", true), std::make_tuple("1-5 a", "aaaa", true),
        std::make_tuple("1-5 a", "aaaaa", false)));
