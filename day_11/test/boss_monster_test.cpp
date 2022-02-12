#include "ferry.hpp"
#include <gtest/gtest.h>

TEST(Part1Example, Step)
{
    auto const input = R"(
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

    auto const final = R"(
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

    Ferry updated_ferry { initial_ferry };
    for (int i = 0; i != 5; ++i) {
        updated_ferry = updated_ferry.step();
    }

    ASSERT_EQ(updated_ferry, final_ferry);
}
