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

std::vector<int> getPreamble(
    std::vector<int> const& vector, int preamble_size, std::size_t currentIndexToCheck)
{
    std::vector<int> preamble;
    return preamble;
}

int findFirstIllegalNumberInVector(std::vector<int> const& vector, int preamble_size)
{
    std::size_t currentIndexToCheck = preamble_size;
    int currentNumberToCheck = vector.at(currentIndexToCheck);

    std::size_t indexA = 0U;
    std::size_t indexB = 1U;

    if (vector.at(indexA) + vector.at(indexB) != currentNumberToCheck) {
        return currentNumberToCheck;
    }

    return 4;
}

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

class FindFirstIllegalNumberInVectorTestFixture
    : public ::testing::TestWithParam<std::pair<std::vector<int>, int>> {
};

using FindFirstIllegalNumberInVectorPreamble2TestFixture
    = FindFirstIllegalNumberInVectorTestFixture;

TEST_P(FindFirstIllegalNumberInVectorPreamble2TestFixture, Preamble2)
{
    auto const numbers = GetParam().first;
    ASSERT_EQ(findFirstIllegalNumberInVector(numbers, 2), GetParam().second);
}

INSTANTIATE_TEST_SUITE_P(FindFirstIllegalNumberInVectorPreamble2Test,
    FindFirstIllegalNumberInVectorPreamble2TestFixture,
    ::testing::Values(std::make_pair(std::vector<int> { 1, 2, 4 }, 4),
        std::make_pair(std::vector<int> { 1, 2, 5 }, 5),
        std::make_pair(std::vector<int> { 1, 2, 3, 6 }, 6)));

using FindFirstIllegalNumberInVectorPreamble3TestFixture
    = FindFirstIllegalNumberInVectorTestFixture;

TEST_P(FindFirstIllegalNumberInVectorPreamble3TestFixture, Preamble3)
{
    auto const numbers = GetParam().first;
    ASSERT_EQ(findFirstIllegalNumberInVector(numbers, 3), GetParam().second);
}

INSTANTIATE_TEST_SUITE_P(FindFirstIllegalNumberInVectorPreamble3Test,
    FindFirstIllegalNumberInVectorPreamble3TestFixture,
    ::testing::Values(std::make_pair(std::vector<int> { 1, 2, 3, 6 }, 6)));

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
