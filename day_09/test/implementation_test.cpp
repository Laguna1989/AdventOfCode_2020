#include "../src/implementation.hpp"
#include "gtest/gtest.h"

using namespace ::testing;

class NumberCanBeConstructedFromPreambleTestFixture
    : public ::testing::TestWithParam<std::pair<std::vector<std::uint64_t>, std::uint64_t>> {
};
using NumberCanBeConstructedFromPreambleTrueTestFixture
    = NumberCanBeConstructedFromPreambleTestFixture;

TEST_P(NumberCanBeConstructedFromPreambleTrueTestFixture, TrueResult1)
{
    ASSERT_TRUE(numberCanBeConstructedFromPreamble(GetParam().first, GetParam().second));
}

INSTANTIATE_TEST_SUITE_P(NumberCanBeConstructedFromPreambleTrueTest,
    NumberCanBeConstructedFromPreambleTrueTestFixture,
    ::testing::Values(std::make_pair(std::vector<std::uint64_t> { 1, 2 }, 3),
        std::make_pair(std::vector<std::uint64_t> { 1, 3 }, 4),
        std::make_pair(std::vector<std::uint64_t> { 1, 3, 5 }, 8),
        std::make_pair(std::vector<std::uint64_t> { 1, 3, 5 }, 4),
        std::make_pair(std::vector<std::uint64_t> { 1, 3, 5 }, 6)));

using NumberCanBeConstructedFromPreambleFalseTestFixture
    = NumberCanBeConstructedFromPreambleTestFixture;

TEST_P(NumberCanBeConstructedFromPreambleFalseTestFixture, TrueResult1)
{
    ASSERT_FALSE(numberCanBeConstructedFromPreamble(GetParam().first, GetParam().second));
}

INSTANTIATE_TEST_SUITE_P(NumberCanBeConstructedFromPreambleTrueTest,
    NumberCanBeConstructedFromPreambleFalseTestFixture,
    ::testing::Values(std::make_pair(std::vector<std::uint64_t> { 1, 2 }, 4),
        std::make_pair(std::vector<std::uint64_t> { 1, 2 }, 1),
        std::make_pair(std::vector<std::uint64_t> { 1, 2, 3 }, 1),
        std::make_pair(std::vector<std::uint64_t> { 1, 2, 3 }, 6)));

TEST(GetPreambleTest, GetPreambleReturnsCorrectValues)
{
    std::vector<std::uint64_t> numbers { 1, 2, 3, 5 };
    int preamble_size = 3;
    std::size_t indexToCheck = 3;

    auto result = getPreamble(numbers, preamble_size, indexToCheck);
    std::vector<std::uint64_t> expectedResult = { 1, 2, 3 };

    EXPECT_EQ(result, expectedResult);
}

TEST(GetPreambleTest, GetPreambleReturnsCorrectValues2)
{
    std::vector<std::uint64_t> numbers { 1, 2, 3, 5, 6, 7, 10 };
    int preamble_size = 3;
    std::size_t indexToCheck = 6;

    auto result = getPreamble(numbers, preamble_size, indexToCheck);
    std::vector<std::uint64_t> expectedResult = { 5, 6, 7 };

    EXPECT_EQ(result, expectedResult);
}

TEST(GetPreambleTest, GetPreambleReturnsCorrectValues3)
{
    std::vector<std::uint64_t> numbers { 1, 2, 3, 5, 6, 7, 10 };
    int preamble_size = 4;
    std::size_t indexToCheck = 6;

    auto result = getPreamble(numbers, preamble_size, indexToCheck);
    std::vector<std::uint64_t> expectedResult = { 3, 5, 6, 7 };

    EXPECT_EQ(result, expectedResult);
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
    : public ::testing::TestWithParam<std::pair<std::vector<std::uint64_t>, std::uint64_t>> {
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
    ::testing::Values(std::make_pair(std::vector<std::uint64_t> { 1, 2, 4 }, 4),
        std::make_pair(std::vector<std::uint64_t> { 1, 2, 5 }, 5),
        std::make_pair(std::vector<std::uint64_t> { 1, 2, 3, 6 }, 6)));

using FindFirstIllegalNumberInVectorPreamble3TestFixture
    = FindFirstIllegalNumberInVectorTestFixture;

TEST_P(FindFirstIllegalNumberInVectorPreamble3TestFixture, Preamble3)
{
    auto const numbers = GetParam().first;
    ASSERT_EQ(findFirstIllegalNumberInVector(numbers, 3), GetParam().second);
}

INSTANTIATE_TEST_SUITE_P(FindFirstIllegalNumberInVectorPreamble3Test,
    FindFirstIllegalNumberInVectorPreamble3TestFixture,
    ::testing::Values(std::make_pair(std::vector<std::uint64_t> { 1, 2, 3, 6 }, 6)));

TEST(ImplementationTest, ExampleTestPart1)
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

TEST(ImplementationTest, ExampleTestPart2)
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

    ASSERT_EQ(findSumOfEnclosingArrayInString(input, 127), 62);
}

TEST(ImplementationTest, FindSumMiniExample)
{
    constexpr auto input = R"(1
2
3)";

    ASSERT_EQ(findSumOfEnclosingArrayInString(input, 3), 3);
}
