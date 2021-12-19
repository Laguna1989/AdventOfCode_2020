#include "boss_monster_input.hpp"
#include "implementation.hpp"
#include <gtest/gtest.h>

TEST(BossMonsterTest, Part1)
{
    ASSERT_EQ(findFirstIllegalNumberInString(boss_monster_input, 25), 393911906);
}
