#include "count_all_answers.hpp"
#include "gtest/gtest.h"
#include <fstream>

using namespace ::testing;

TEST(BossMonsterTest, ExampleInput)
{
    constexpr auto input = R"(abc

a
b
c

ab
ac

a
a
a
a

b)";

    ASSERT_EQ(11, countQuestionsAnyoneAnsweredYes(input));
}

TEST(BossMonsterTest, BossMonsterTestPart1Full)
{
    std::ifstream file { "puzzle_input.txt" };

    std::stringstream buffer;
    buffer << file.rdbuf();

    ASSERT_EQ(6686, countQuestionsAnyoneAnsweredYes(buffer.str()));
}

TEST(BossMonsterTest, BossMonsterTestPart2Example)
{
    constexpr auto input = R"(abc

a
b
c

ab
ac

a
a
a
a

b)";

    ASSERT_EQ(6, countQuestionsEveryoneAnsweredYes(input));
}

TEST(BossMonsterTest, BossMonsterTestPart2Full)
{
    std::ifstream file { "puzzle_input.txt" };

    std::stringstream buffer;
    buffer << file.rdbuf();

    ASSERT_EQ(3476, countQuestionsEveryoneAnsweredYes(buffer.str()));
}
