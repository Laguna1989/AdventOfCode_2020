#include "ferry.hpp"
#include <gtest/gtest.h>

class FerryParserTestFixture : public ::testing::TestWithParam<std::pair<std::string, bool>> {
};

TEST_P(FerryParserTestFixture, SimpleInputIsParsedCorrectly)
{
    auto const input = GetParam().first;
    auto const expected_is_seat = GetParam().second;
    Ferry f(input);

    ASSERT_EQ(f.is_seat(Position { 0, 0 }), expected_is_seat);
}

INSTANTIATE_TEST_SUITE_P(FerryParserTest, FerryParserTestFixture,
    ::testing::Values(
        std::make_pair("L", true), std::make_pair("#", true), std::make_pair(".", false)));

TEST(FerryParserTest, TwoSeatOneRowInputIsParsedCorrectly)
{
    auto const input = ".#";
    Ferry f(input);

    ASSERT_EQ(f.is_seat(Position { 0, 0 }), false);
}

TEST(FerryParserTest, SecondSeatOfTwoSeatOneRowInputIsParsedCorrectly)
{
    auto const input = ".#";
    Ferry f(input);

    ASSERT_EQ(f.is_seat(Position { 1, 0 }), true);
}

TEST(FerryParserTest, FirstRowOfTwoRowInputIsParsedCorrectly)
{
    auto const input = ".\n#";
    Ferry f(input);

    ASSERT_EQ(f.is_seat(Position { 0, 0 }), false);
}

TEST(FerryParserTest, SecondRowOfTwoRowInputIsParsedCorrectly)
{
    auto const input = ".\n#";
    Ferry f(input);

    ASSERT_EQ(f.is_seat(Position { 0, 1 }), true);
}

TEST(FerryParserTest, ComplexTest)
{
    auto const input = ".##\n#..\n#L.";
    Ferry f(input);

    ASSERT_EQ(f.is_seat(Position { 2, 1 }), false);
    ASSERT_EQ(f.is_seat(Position { 2, 2 }), false);
    ASSERT_EQ(f.is_seat(Position { 1, 2 }), true);
}
