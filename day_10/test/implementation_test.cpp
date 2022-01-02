#include "implementation.hpp"
#include <gtest/gtest.h>

TEST(CalculateProduct, SmallExample)
{
    std::string input = R"(16
10
15
5
1
11
7
19
6
12
4)";
    auto const result = calculateProductOfOneAndThreeJoltDiffString(input);

    EXPECT_EQ(result, 35);
}

TEST(ConversionTest, ConvertToVector)
{
    std::string input = R"(16
10
15
5
1
11
7
19
6
12
4)";
    std::vector<std::uint64_t> const expectation { 16, 10, 15, 5, 1, 11, 7, 19, 6, 12, 4 };
    auto const result = convertToVector(input);

    ASSERT_EQ(expectation, result);
}

TEST(ConversionTest, CalculateDifferences)
{
    std::vector<std::uint64_t> const input { 16, 10, 15, 5, 1, 11, 7, 19, 6, 12, 4 };
    // std::vector<std::uint64_t> const sorted { 1, 4, 5,6,7,10,11,12,15,16,19 };
    std::vector<std::uint64_t> const result = calculateDifferencesOfSortedNumbers(input);
    std::vector<std::uint64_t> const expectation { 1, 3, 1, 1, 1, 3, 1, 1, 3, 1, 3, 3 };
    ASSERT_EQ(expectation, result);
}

TEST(DifferencesTest, NumberOfOnes)
{
    std::vector<std::uint64_t> const input { 1, 3, 1, 1, 1, 3, 1, 1, 3, 1, 3, 3 };
    auto const expectation = 7;
    auto const result = getNumberOfOnesFromDifferences(input);

    ASSERT_EQ(expectation, result);
}
