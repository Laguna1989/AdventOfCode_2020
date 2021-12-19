#include "parser.hpp"
#include <fstream>
#include <gtest/gtest.h>
#include <sstream>

TEST(BossMonsterTest, BossMonsterTestStage1)
{
    std::ifstream file { "boss_monster_input.txt" };
    std::stringstream buffer;
    buffer << file.rdbuf();

    auto const containers = parseMultipleLines(buffer.str());
    auto const list = listValidContainers(containers, "shiny gold");
    ASSERT_EQ(list.size(), 287);
}

TEST(BossMonsterTest, SmallBossMonsterPart2)
{
    std::string const input = R"(light red bags contain 1 bright white bag, 2 muted yellow bags.
dark orange bags contain 3 bright white bags, 4 muted yellow bags.
bright white bags contain 1 shiny gold bag.
muted yellow bags contain 2 shiny gold bags, 9 faded blue bags.
shiny gold bags contain 1 dark olive bag, 2 vibrant plum bags.
dark olive bags contain 3 faded blue bags, 4 dotted black bags.
vibrant plum bags contain 5 faded blue bags, 6 dotted black bags.
faded blue bags contain no other bags.
dotted black bags contain no other bags.)";

    auto const containers = parseMultipleLines(input);
    auto const needed = neededContainersFor(containers, "shiny gold");
    ASSERT_EQ(needed, 32);
}

TEST(BossMonsterTest, MediumBossMonsterPart2)
{
    std::string const input = R"(shiny gold bags contain 2 dark red bags.
dark red bags contain 2 dark orange bags.
dark orange bags contain 2 dark yellow bags.
dark yellow bags contain 2 dark green bags.
dark green bags contain 2 dark blue bags.
dark blue bags contain 2 dark violet bags.
dark violet bags contain no other bags.)";

    auto const containers = parseMultipleLines(input);
    auto const needed = neededContainersFor(containers, "shiny gold");
    ASSERT_EQ(needed, 126);
}

TEST(BossMonsterTest, BossMonsterPart2)
{
    std::ifstream file { "boss_monster_input.txt" };
    std::stringstream buffer;
    buffer << file.rdbuf();

    auto const containers = parseMultipleLines(buffer.str());
    auto const needed = neededContainersFor(containers, "shiny gold");
    ASSERT_EQ(needed, 48160);
}