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

TEST(CalculateProduct, BigExample)
{
    std::string input = R"(28
33
18
42
31
14
46
20
48
47
24
23
49
45
19
38
39
11
1
32
25
35
8
17
7
9
4
2
34
10
3)";
    auto const result = calculateProductOfOneAndThreeJoltDiffString(input);

    EXPECT_EQ(result, 220);
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
    std::vector<std::uint64_t> const result = sortAndCalculateDifferencesOfNumbers(input);
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

TEST(DifferencesTest, NumberOfThrees)
{
    std::vector<std::uint64_t> const input { 1, 3, 1, 1, 1, 3, 1, 1, 3, 1, 3, 3 };
    auto const expectation = 5;
    auto const result = getNumberOfThreesFromDifferences(input);

    ASSERT_EQ(expectation, result);
}

TEST(CombinationTest, SmallExample)
{
    std::vector<std::uint64_t> const input { 16, 10, 15, 5, 1, 11, 7, 19, 6, 12, 4 };
    auto const expectation = 8;
    auto const result = calculateNumberOfCombinationsForInput(input);

    ASSERT_EQ(expectation, result);
}

TEST(CombinationTest, MinimalExample1)
{
    std::vector<std::uint64_t> const input { 1,4,7,10 };
    auto const expectation = 1;
    auto const result = calculateNumberOfCombinationsForInput(input);

    ASSERT_EQ(expectation, result);
}

TEST(CombinationTest, MinimalExample2A)
{
    std::vector<std::uint64_t> const input { 1,2,4,7,10 };
    auto const expectation = 3;
    auto const result = calculateNumberOfCombinationsForInput(input);

    ASSERT_EQ(expectation, result);
}

TEST(CombinationTest, MinimalExample2B)
{
    std::vector<std::uint64_t> const input { 1,4,7,9,10 };
    auto const expectation = 2;
    auto const result = calculateNumberOfCombinationsForInput(input);

    ASSERT_EQ(expectation, result);
}

TEST(CombinationTest, MinimalExample2C)
{
    std::vector<std::uint64_t> const input { 1,4,7,8,10 };
    auto const expectation = 2;
    auto const result = calculateNumberOfCombinationsForInput(input);

    ASSERT_EQ(expectation, result);
}

TEST(CombinationTest, BigExample)
{
    std::string input = R"(28
33
18
42
31
14
46
20
48
47
24
23
49
45
19
38
39
11
1
32
25
35
8
17
7
9
4
2
34
10
3)";
    auto const vec = convertToVector(input);
    auto const expectation = 19208;
    auto const result = calculateNumberOfCombinationsForInput(vec);

    ASSERT_EQ(expectation, result);
}
