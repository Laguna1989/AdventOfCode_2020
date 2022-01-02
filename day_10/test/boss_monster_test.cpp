#include "boss_monster_input.hpp"
#include "implementation.hpp"
#include <gtest/gtest.h>

TEST(BossMonsterTest, Part1)
{
    auto const result = calculateProductOfOneAndThreeJoltDiffString(boss_monster_input);
    ASSERT_EQ(result, 2176);
}

TEST(BossMonsterTest, Part2)
{
    auto const vec = convertToVector(boss_monster_input);
    auto const expectation = 18512297918464;
    auto const result = calculateNumberOfCombinationsForInput(vec);

    ASSERT_EQ(expectation, result);
}
