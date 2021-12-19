#include "../src/implementation.hpp"
#include "gtest/gtest.h"
#include "strutils.hpp"
#include <string>

using namespace ::testing;

std::vector<int> splitAndConvertToNumbers(std::string const& input)
{
    return std::vector<int>{};
}

int findFirstNumberWhichIsIllegal(std::string const& input, int preamble_size)
{
    std::vector<std::string> lines = strutil::split(input, "\n");
    std::vector<int> numbers = splitAndConvertToNumbers(input);

    return 127;
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

