#include "boss_monster_input.hpp"
#include "implementation.hpp"
#include <gtest/gtest.h>

TEST(BossMonsterTest, Part1)
{
    auto const result = calculateProductOfOneAndThreeJoltDiffString(boss_monster_input);
    ASSERT_EQ(result, 2176);
}
