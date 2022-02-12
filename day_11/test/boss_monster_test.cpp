#include "ferry.hpp"
#include <gtest/gtest.h>

Ferry find_steady_state(Ferry const& ferry){
    Ferry temp{ferry};
    while(true){
        auto old_ferry =temp;
        temp = temp.step();
        if(old_ferry == temp){
            return temp;
        }
    }
    return Ferry{""};
}

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

    Ferry updated_ferry = find_steady_state(initial_ferry);

    ASSERT_EQ(updated_ferry, final_ferry);
}
