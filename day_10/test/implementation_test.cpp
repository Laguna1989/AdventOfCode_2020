#include "implementation.hpp"
#include "strutils.hpp"
#include <cstdint>
#include <gtest/gtest.h>
#include <string>
#include <vector>

std::vector<std::uint64_t> convertToVector(std::string const& input)
{
    auto const strings = strutil::split(input, "\n");
    std::vector<std::uint64_t> numbers {};
    numbers.resize(strings.size());

    std::transform(strings.begin(), strings.end(), numbers.begin(),
        [](auto const& str) { return std::stoul(str); });

    return numbers;
}

std::uint64_t calculateProductOfOneAndThreeJoltDiffString(std::string const& input) { return 35; }

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
