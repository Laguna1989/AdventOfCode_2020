#include "boss_monster_input.hpp"
#include "implementation.hpp"
#include <gtest/gtest.h>

TEST(BossMonsterTest, Part1)
{
    ASSERT_EQ(findFirstIllegalNumberInString(boss_monster_input, 25), 393911906);
}

TEST(BossMonsterTest, Part2)
{
    auto const illegalNumber = findFirstIllegalNumberInString(boss_monster_input, 25);
    ASSERT_EQ(findSumOfEnclosingArrayInString(boss_monster_input, illegalNumber), 59341885);
}
