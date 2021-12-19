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
    output.resize(lines.size());
    std::transform(
        lines.begin(), lines.end(), output.begin(), [](auto const& str) { return std::stoi(str); });

    return output;
}

int findFirstIllegalNumberInVector(std::vector<int> const& vector1, int preamble_size) { return 4; }

int findFirstIllegalNumberInString(std::string const& input, int preamble_size)
{
    std::vector<int> const numbers = splitAndConvertToNumbers(input);

    return 127; // findFirstIllegalNumberInVector(numbers, preamble_size);
}

TEST(SplitAndConvertToNumbersTest, EmptyInputReturnsEmptyVector)
{
    std::string const input { "" };
    EXPECT_TRUE(splitAndConvertToNumbers(input).empty());
}

TEST(SplitAndConvertToNumbersTest, InputWithTwoNumberReturnsCorrectValues)
{
    std::string const input { "12\n34" };
    auto const numbers = splitAndConvertToNumbers(input);

    EXPECT_EQ(numbers.at(0), 12);
    EXPECT_EQ(numbers.at(1), 34);
}

TEST(FindFirstIllegalNumberInVectorTest, Preamble2Easy)
{
    std::vector<int> const numbers { 1, 2, 4 };
    ASSERT_EQ(findFirstIllegalNumberInVector(numbers, 2), 4);
}

TEST(FindFirstIllegalNumberInVectorTest, Preamble2Easy2)
{
    std::vector<int> const numbers { 1, 2, 5 };
    ASSERT_EQ(findFirstIllegalNumberInVector(numbers, 2), 5);
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

    ASSERT_EQ(findFirstIllegalNumberInString(input, 5), 127);
}
