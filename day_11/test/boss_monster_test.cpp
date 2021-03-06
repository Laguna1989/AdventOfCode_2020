#include "boss_monster_input.hpp"
#include "ferry.hpp"
#include <gtest/gtest.h>

Ferry find_steady_state(Ferry const& ferry)
{
    Ferry temp { ferry };
    while (true) {
        auto old_ferry = temp;
        temp = temp.step();
        if (old_ferry == temp) {
            return temp;
        }
    }
    return Ferry { "" };
}

TEST(Part1Example, FindFinalState)
{
    constexpr auto input = R"(
L.LL.LL.LL
LLLLLLL.LL
L.L.L..L..
LLLL.LL.LL
L.LL.LL.LL
L.LLLLL.LL
..L.L.....
LLLLLLLLLL
L.LLLLLL.L
L.LLLLL.LL)";

    Ferry const initial_ferry { input };

    constexpr auto final = R"(
#.#L.L#.##
#LLL#LL.L#
L.#.L..#..
#L##.##.L#
#.#L.LL.LL
#.#L#L#.##
..L.L.....
#L#L##L#L#
#.LLLLLL.L
#.#L#L#.##)";

    Ferry const final_ferry { final };

    Ferry const updated_ferry = find_steady_state(initial_ferry);

    ASSERT_EQ(updated_ferry, final_ferry);
}

TEST(BossMonsterTest, Part1)
{
    Ferry initial_ferry { boss_monster_input };
    Ferry updated_ferry = find_steady_state(initial_ferry);
    auto number_of_occupied_seats = updated_ferry.get_number_of_occupied_seats();

    ASSERT_EQ(number_of_occupied_seats, 2481);
}

TEST(Part2Example, Step)
{
    constexpr auto input = R"(
L.LL.LL.LL
LLLLLLL.LL
L.L.L..L..
LLLL.LL.LL
L.LL.LL.LL
L.LLLLL.LL
..L.L.....
LLLLLLLLLL
L.LLLLLL.L
L.LLLLL.LL)";

    Ferry initial_ferry { input };

    constexpr auto final = R"(
#.##.##.##
#######.##
#.#.#..#..
####.##.##
#.##.##.##
#.#####.##
..#.#.....
##########
#.######.#
#.#####.##)";

    Ferry const final_ferry { final };

    Ferry const updated_ferry = initial_ferry.step();

    ASSERT_EQ(updated_ferry, final_ferry);
}

TEST(Part2Example, FindFinalState)
{
    constexpr auto input = R"(
L.LL.LL.LL
LLLLLLL.LL
L.L.L..L..
LLLL.LL.LL
L.LL.LL.LL
L.LLLLL.LL
..L.L.....
LLLLLLLLLL
L.LLLLLL.L
L.LLLLL.LL)";

    Ferry initial_ferry { input };

    constexpr auto final = R"(
#.L#.L#.L#
#LLLLLL.LL
L.L.L..#..
##L#.#L.L#
L.L#.LL.L#
#.LLLL#.LL
..#.L.....
LLL###LLL#
#.LLLLL#.L
#.L#LL#.L#)";

    Ferry const final_ferry { final };

    Ferry const updated_ferry = find_steady_state(initial_ferry);

    ASSERT_EQ(updated_ferry, final_ferry);
}

TEST(BossMonsterTest, Part2)
{
    Ferry initial_ferry { boss_monster_input };
    Ferry updated_ferry = find_steady_state(initial_ferry);
    auto number_of_occupied_seats = updated_ferry.get_number_of_occupied_seats();

    ASSERT_EQ(number_of_occupied_seats, 2227);
}
