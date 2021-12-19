#include "landscape.hpp"
#include "position.hpp"
#include "gtest/gtest.h"
#include <tuple>
#include <vector>

using namespace ::testing;

class LandscapeSizeTestFixture
    : public ::testing::TestWithParam<std::tuple<std::string, std::size_t, std::size_t>> {
public:
    std::unique_ptr<Landscape> landscape;
    std::size_t expectedX;
    std::size_t expectedY;

    void SetUp() override
    {
        landscape = std::make_unique<Landscape>(std::get<0>(GetParam()));
        expectedX = std::get<1>(GetParam());
        expectedY = std::get<2>(GetParam());
    }
};

TEST_P(LandscapeSizeTestFixture, SizeX) { ASSERT_EQ(landscape->sizeX(), expectedX); }

TEST_P(LandscapeSizeTestFixture, SizeY) { ASSERT_EQ(landscape->sizeY(), expectedY); }

constexpr auto example_input = R"(..##.......
#...#...#..
.#....#..#.
..#.#...#.#
.#...##..#.
..#.##.....
.#.#.#....#
.#........#
#.##...#...
#...##....#
.#..#...#.#)";

INSTANTIATE_TEST_SUITE_P(LandscapeSizeTest, LandscapeSizeTestFixture,
    ::testing::Values(std::make_tuple(example_input, 11u, 11u),
        std::make_tuple(R"(..
..)",
            2u, 2u),
        std::make_tuple(R"(.##
.#.)",
            3u, 2u)));

class LandscapeTreeAtPositionTestFixture
    : public ::testing::TestWithParam<std::tuple<std::string, Position, bool>> {
public:
    std::unique_ptr<Landscape> landscape;
    Position position;
    bool expectedResult;

    void SetUp() override
    {
        landscape = std::make_unique<Landscape>(std::get<0>(GetParam()));
        position = std::get<1>(GetParam());
        expectedResult = std::get<2>(GetParam());
    }
};

TEST_P(LandscapeTreeAtPositionTestFixture, HasTreeAt)
{
    ASSERT_EQ(landscape->hasTreeAt(position), expectedResult);
}

INSTANTIATE_TEST_SUITE_P(LandscapeTreeAtPositionTest, LandscapeTreeAtPositionTestFixture,
    ::testing::Values(std::make_tuple(R"(.##
.#.)",
                          Position { 1, 1 }, true),
        std::make_tuple(R"(.##
.#.)",
            Position { 0, 0 }, false),
        std::make_tuple(example_input, Position { 0, 1 }, true),
        std::make_tuple(example_input, Position { 10, 10 }, true),
        std::make_tuple(example_input, Position { 11, 0 }, false),
        std::make_tuple(R"(..
#.)",
            Position { 5, 0 }, false),
        std::make_tuple(R"(..
#.)",
            Position { 5, 1 }, false)));

class LandscapeCountTreesTestFixture
    : public ::testing::TestWithParam<std::tuple<std::string, Slope, std::size_t>> {
public:
    std::unique_ptr<Landscape> landscape;
    Slope slope;
    std::size_t expectedResult;

    void SetUp() override
    {
        landscape = std::make_unique<Landscape>(std::get<0>(GetParam()));
        slope = std::get<1>(GetParam());
        expectedResult = std::get<2>(GetParam());
    }
};

TEST_P(LandscapeCountTreesTestFixture, CorrectAmount)
{
    ASSERT_EQ(landscape->countTrees(slope), expectedResult);
}

INSTANTIATE_TEST_SUITE_P(LandscapeCountTreesTest, LandscapeCountTreesTestFixture,
    ::testing::Values(std::make_tuple(example_input, Slope { 3, 1 }, 7),
        std::make_tuple("..\n..", Slope { 1, 1 }, 0),
        std::make_tuple("##\n##", Slope { 1, 1 }, 2)));

constexpr auto bossMonsterInput = R"(.##......#.##..#..#..##....#...
...##.....#...###........###...
#....##....#.....#.....#..##.##
.......#.###.#......#..#..#..#.
##..........#....#.#...#.......
###.#.#.#......##...#..........
.#.##........#..............#..
..#..........#...##..#.......##
.........##...#...#....###.#...
#.......#.....#.#.#...###.##.#.
...#...#...#......#........#.##
....#..........#.....#..#....##
.#.#.##....#.#...#.............
#....#..#.....#.#..............
........#....#....#..#........#
..#.......#...#....##.#........
......#.........##.......#.#...
............#.......#..........
.....#..#.#..#........##...#...
....#.....................###..
..#.......#.........#..##....##
..#........#..#...#........#...
..............#....##..##....#.
....#..#.#.......#....#..#...##
.#........##......#.#..#.#.....
............#.##...##...#...##.
.......#........#.........##...
...#...........#.#...#..#......
#...#............#..####.......
..#..#..#..#.....#...#.#.#.....
....#.#..............#.....##..
#.....##........#......#.......
.....#..#................##.#..
.###.#...................#.....
....#....#...#.##..........#...
.#.....#....#.......#...#......
.....#...#.##.##............#..
..........#..#....#...#.#..#...
#...#..#..............###.#...#
......#....#.#....##....#......
............#......#......##...
.#....#...#........#.#.#..#....
..#.....#.......#.....#.#......
#....#......#.......#......#...
....#..##.....#...#........#...
.#..#......#..#................
.#...#...#....#.#...#.....#...#
......#..#...#...#..#.......##.
...#..#...#.#.......#.......#..
..#...#.........#......#......#
......#...#..#..........#......
.#..#......#....#.#.#...#....#.
.#.#....#.#.#..#..#..#........#
....###.#...##..#.#..#....#....
...#.#.#................#......
.#.....#..#..........##..#....#
..........#..#......#.........#
.....#....#...#.#..##....#.#.#.
........#.##......###..........
##......#.#..#.....#..##.#.....
.#.......#..#....##.....##.....
.....##....#...................
##......#....##........#.....#.
..##...#...........##........#.
...#....#..##.#....#......##...
#....#...##....#..........#....
......##....#...............#..
...#.#.#...#...#...#...........
....#..#...#.#....#.#......#...
.......#...#...............#...
.##..#....#...#....#.#........#
.....#..##............#......#.
...##...#.....#..........#.#..#
..#..##.............#....#.....
.....#.#.....#.........#......#
........#..........#.#.#...#..#
#........#.#...................
......#......##..............#.
......#..#.#.....#...#.#...#...
.#..##.....#...##.......#......
#.......#....#..##....#..#.#...
#..#..#....#...........#.##....
..##....#....##.....#...#...##.
.#.......#.......#....#.......#
.#..#..#...#...#...............
.#..............#.....#........
..........##...#....#.#......##
..........#..........#.......#.
..#..##....##...#.......#......
.#......#.#........##.#........
...#......#..#....#...#....#...
...............#....#..#.##...#
....#.......................#..
#....##.#......#....#..........
.......#.#......#........#..##.
..#.....#...#...........##..#..
#........#.#....#............#.
.........##..................#.
........#...#..#...#......#...#
...#.......#...####.#...#......
....#..###......###..#.........
.....#...........#......#......
.#.....#......#.....#.....##.##
.#.#...##..........#........#.#
..#....#.....##...............#
.....##.....#...##..#..........
.#......##.......#..##.##.#...#
.#..#...#.##.....#.#...........
.........#....##...#.....##....
#..........#.............#..#.#
...........#........#.#...#....
........#..###...#...........#.
#.........#...#....#..##.##....
........#....##.......#.#....#.
..........#..............#.....
....##...#...##..........#.....
...#..##.#...###..#............
...##..#####....#.............#
.#..#.......##.......#........#
....##..........#.......#.#....
......#.........####.......#...
...............#......#..#.....
...#...##...#.#.#.....##.#.#...
..#....#..#..............#....#
#..............#............#..
.#.#..#....#.....#.#.#...#.....
......#......#..#..#.....#.....
.#.#..#.##.#........#..........
..##.#......#..#.......#.......
.##...##....#..#.#.........#.##
.........#........#.#..###....#
.....#...............#.........
......##..........#.....#......
.#.....#.#.#..#.#.....#..#.####
.......###.##......#.....#.#..#
..#.....#....#.#.##......#....#
.....##..#................#..##
.#......#.....#..#.....#..#####
.........#.#.......#..##...#...
.#.#..#.......##.....#....#....
.....#...###.#...#......#....#.
.#....#....#...#..#.#........#.
......##........##.#...#..#..#.
.##.##.###..#.....#........###.
.....#..#.#.......#..#.#.......
##.#.#..............#..##......
....#.........#.......#.#......
.....#..#.....#...#.#....#.#...
...#..#.#.#..................#.
........##.#.###...............
..#...#.#.......#......#.......
.......#.##....#...#....#......
......#.#.............#........
........#......#........##.##..
.....#...#......##.............
...#.#..#.....#.#...#..........
.#.#..#.....#............#.....
.#.#..#.#.##.#...#.##..##...#..
.........##........#.##..#.....
##.#.#......###..#.##.#........
.##...#..#...#.#..#....##.....#
#......#..........#.#...#.....#
..........#......#...#.......#.
.............#..........#......
#.#....#.......##..#.....#.#...
##......#..#......#.#..#.#....#
..#.#..#.....#.#......#....#..#
...#......#......##.....#..#.#.
....#......#.....#....#.#.#..#.
.....#..#..#.....#...........##
....#.....#...#........##.#.#.#
..#......#.......#........#....
#.......##..##......#...####..#
#..........#......#.#..#..#....
.................##............
...#..#..#.#.....#.##.#.....#.#
...#....###....................
....#.......#..#.#.............
#......#................#......
..........#........#..#........
.....#......##..#......#..###..
...#....#.......#..............
.#....#.#.#........#.....#...#.
.......#.....##.#.....#....#...
.........#.#.........##..#...#.
......#......#....#.....##.#.#.
####...#.........#.....#......#
...#.#..#..#.............#.....
......#.........#....#.#..##..#
.........#.....#.#..##..##..#..
.#......##.............#.......
....#...#......#...#.....#.#.##
......#..##....#..#.....#......
......#..............#....##...
.........#.###..........#.##...
#....#..........#..#.......#...
...........#...#.....#.......#.
..#..#........#................
...###.........#...............
.....#.##...#.................#
..#.#..#...###......#........#.
#......#......#.#.............#
.........#.#.....#..#........#.
........#..#......#......##....
.....#......#...#.....##...#.##
.##...#..#....##..........###..
.......#............#........##
.##.....#.......#...#..........
..###..........#.............##
#....#....#.#....#............#
#...#......................#...
....#..#..#..#.......###....#..
#..###.#..#.....#.............#
..........#.##.....#.........##
...#.............#....#....##..
#........................#..#..
........#...#.....#.....#..##..
#........#......#....#..#....#.
.....#.#.#....#.#..#....#......
.....#....#....................
.........#..#..#....#......#...
..........#.#.#.......#........
.......#.#.....#..#.....##.....
.....#....#.#.....#.......#..#.
.#..###.......#......#..#..#...
..##.#.....#.........##.#......
.....#.......###.......##......
#...#.......##.#.#......#.....#
.##........##.#...#...#........
....#.......#....#..#.......#..
.#..#.......#..####..##........
..#..#..#..#..#..#.............
...#......#...#...#.#......##.#
........#.#..#.#.#......#...#..
#.......#..##.......##........#
..##...#...............#.#....#
.####........##..........#..#..
..#........#...##...#........#.
.#.#..........#...#...#........
....###..........#....#........
.#.#.#.###.#.##..#.#........#..
..........#....##.#..##........
.......#..#..##.......#........
..#........#....#..####.#..#...
....#.......#..##..#..........#
.....#...........#....#....#...
.#.##..#......##.........#.#...
...#......##..##......#.....#..
#........#..........#.#...#....
.#.#........###........#..#....
....#####.................##...
.........##...#......#.........
.......#....#....#.#....#...#..
......#................#...#.#.
....#.....#.....#.#.....#.....#
#.........#..#........#.....#..
....#...........#.....#.#......
##..#....................#.#...
#.#.##....#.....##....#.......#
..#..#....###.......#..##......
......##.....#.##...#....#..#..
........#..#.#..#..#.#.........
#...#.....##..........##.......
....#.....#...#.###.......#....
..........#..#...#........##..#
##..#...#.#.####.#..#..#...#...
................#......#..#....
.......#...###...#........#....
....#..##..#.#......#...#.#..##
.##......#...........#.......##
....#.#...#..#.#.......##......
....#..##..#.....#........##...
...#...#..#.#.#....#.........#.
#....##.#....#..##.............
.#......##......#.#.##.......#.
.......#...#....#.##......#....
..##..........#.....#.#......#.
#..##.....#..........##..#.#...
....#.#.......#.#.....#.....#..
##.....#..#.....##...#.....#..#
...#.#..#...#..............#...
...............#..#............
.#.......#......#........##....
..#......#..##..####.....#...#.
.#.##.#.#..#..##..##...........
...##.............#.....#..#...
.##.....#..#.#......##........#
##....#.............#...#......
......#.....###...........##...
.#.#...#.............##..#..###
..#.##.##...#.....#...........#
.....#.....##...#...#........#.
........#..##.......##.....#...
.#........####.......#.#...#...
...#..........#......##........
.......#......#..##..#...#.....
..#...........#.#.#..#.#.#.....
#..........#....#....###.#.....
....#.................#...##...
#....#.###......#..#.....#...##
.#.......##.....###.....#...#..
....##............#...........#
...#.#.#.........#...#..#..#..#
.....#..###.................#..
.#.....#.....#....###.#..#...#.
................#...#..........
..#....#..##....#.##........#..
....##....#...........#..#.....
...##......###.......#...#.....
.......##............#......#.#
#####.....#..#.###..#.#........
#.##.##..#.......#....#........
....###..#.#.#......###.#......
....#....#.....##.#..#....#...#
....#.....#.#...##.##.#.#....#.
.........#.#.###.#.....#.......
.#....#.......#..##...#....#...
...####...##.#.....#...........
#.....#.....#..........##..#...
................#.#.#......#...
.#...#.......#..#............#.
.##.#.......#..#....#.....#....
.#...#..#.....#..............#.)";

TEST(LandscapeCountTreesTest, BossMonsterTestStage1)
{
    Landscape l { bossMonsterInput };
    Slope p { 3, 1 };

    EXPECT_EQ(l.countTrees(p), 265);
}

TEST(LandscapeCountTreesTest, BossMonsterTestStage2)
{
    Landscape l { bossMonsterInput };

    std::vector<Slope> slopes {
        Slope { 1, 1 },
        Slope { 3, 1 },
        Slope { 5, 1 },
        Slope { 7, 1 },
        Slope { 1, 2 },
    };

    std::uint64_t result = 1;
    for (auto const& s : slopes) {
        result *= static_cast<std::uint64_t>(l.countTrees(s));
    }
    ASSERT_EQ(result, 3154761400);
}