#include "../src/implementation.hpp"
#include "strutils.hpp"
#include "gtest/gtest.h"
#include <string>

using namespace ::testing;

std::vector<int> splitAndConvertToNumbers(std::string const& input)
{
    if (input.empty()) {
        return {};
    }

    std::vector<std::string> lines = strutil::split(input, "\n");

    std::vector<int> output;
    std::transform(lines.begin(), lines.end(), std::back_inserter(output),
        [](auto const& str) { return std::stoi(str); });

    return output;
}

int findFirstNumberWhichIsIllegal(std::string const& input, int preamble_size)
{
    std::vector<int> numbers = splitAndConvertToNumbers(input);

    return 127;
}

TEST(SplitAndConvertToNumbersTest, EmptyInputReturnsEmptyVector)
{
    std::string input = "";
    EXPECT_TRUE(splitAndConvertToNumbers(input).empty());
}

TEST(SplitAndConvertToNumbersTest, InputWithTwoNumberReturnsCorrectValues)
{
    std::string input = "12\n34";
    auto const numbers = splitAndConvertToNumbers(input);

    EXPECT_EQ(numbers.at(0), 12);
    EXPECT_EQ(numbers.at(1), 34);
}

TEST(ImplementationTest, ExampleTest)
{
    constexpr auto input = R"(35
20
15
25
47
40
62
55
65
95
102
117
150
182
127
219
299
277
309
576)";

    ASSERT_EQ(findFirstNumberWhichIsIllegal(input, 5), 127);
}
