#include "ferry.hpp"
#include <gtest/gtest.h>

class FerryParserTestFixture : public ::testing::TestWithParam<std::string> {
};

TEST_P(FerryParserTestFixture, SimpleInputReturnsCorrectIsSeat)
{
    auto const input = GetParam();
    auto const expected_is_seat = input != ".";
    Ferry f(input);

    ASSERT_EQ(f.is_seat(Position { 0, 0 }), expected_is_seat);
}

TEST_P(FerryParserTestFixture, SimpleInputReturnsCorrectIsOccupiedSeat)
{
    auto const input = GetParam();
    auto const expected_is_occupied_seat = input == "#";
    Ferry f(input);

    ASSERT_EQ(f.is_occupied_seat(Position { 0, 0 }), expected_is_occupied_seat);
}

INSTANTIATE_TEST_SUITE_P(FerryParserTest, FerryParserTestFixture, ::testing::Values("L", "#", "."));

TEST(FerryParserTest, TwoSeatOneRowInputIsParsedCorrectly)
{
    auto const input = ".#";
    Ferry f(input);

    ASSERT_EQ(f.is_seat(Position { 0, 0 }), false);
}

TEST(FerryParserTest, SecondSeatOfTwoSeatOneRowInputIsParsedCorrectly)
{
    auto const input = ".#";
    Ferry f(input);

    ASSERT_EQ(f.is_seat(Position { 1, 0 }), true);
}

TEST(FerryParserTest, FirstRowOfTwoRowInputIsParsedCorrectly)
{
    auto const input = ".\n#";
    Ferry f(input);

    ASSERT_EQ(f.is_seat(Position { 0, 0 }), false);
}

TEST(FerryParserTest, SecondRowOfTwoRowInputIsParsedCorrectly)
{
    auto const input = ".\n#";
    Ferry f(input);

    ASSERT_EQ(f.is_seat(Position { 0, 1 }), true);
}

TEST(FerryParserTest, ComplexTest)
{
    auto const input = ".##\n#..\n#L.";
    Ferry f(input);

    ASSERT_EQ(f.is_seat(Position { 2, 1 }), false);
    ASSERT_EQ(f.is_seat(Position { 2, 2 }), false);
    ASSERT_EQ(f.is_seat(Position { 1, 2 }), true);
}

TEST(FerryParserTest, ReallyComplexTestIsSeat)
{
    auto const input = R"(L.LL.LL.LL
LLLLLLL.LL
L.L.L..L..
LLLL.LL.LL
L.LL.LL.LL
L.LLLLL.LL
..L.L.....
LLLLLLLLLL
L.LLLLLL.L
L.LLLLL.LL)";
    Ferry f(input);

    ASSERT_EQ(f.is_seat(Position { 0, 0 }), true);
    ASSERT_EQ(f.is_seat(Position { 7, 1 }), false);
}

TEST(FerryParserTest, ReallyComplexTestNumberOfOccupiedSeats)
{
    auto const input = R"(L.LL.LL.LL
LLLLLLL.LL
L.L.L..L..
LLLL.LL.LL
L.LL.LL.LL
L.LLLLL.LL
..L.L.....
LLLLLLLLLL
L.LLLLLL.L
L.LLLLL.LL)";
    Ferry f(input);

    ASSERT_EQ(f.get_number_of_occupied_seats(), 0);
}

TEST(FerryParserTest, ReallyComplexFinalTestNumberOfOccupiedSeats)
{
    auto const input = R"(#.#L.L#.##
#LLL#LL.L#
L.#.L..#..
#L##.##.L#
#.#L.LL.LL
#.#L#L#.##
..L.L.....
#L#L##L#L#
#.LLLLLL.L
#.#L#L#.##)";
    Ferry f(input);

    ASSERT_EQ(f.get_number_of_occupied_seats(), 37);
}

TEST(FerryRulesTest, UnoccupiedSeatWithoutOccupiedNeighboursGetsOccupied)
{
    auto const input = "L";
    Ferry initial_ferry(input);

    Ferry updated_ferry = initial_ferry.step();

    ASSERT_EQ(updated_ferry.is_occupied_seat(Position { 0, 0 }), true);
}

TEST(FerryRulesTest, OccupiedSeatWithoutOccupiedNeighboursStaysOccupied)
{
    auto const input = "#";
    Ferry initial_ferry(input);

    Ferry updated_ferry = initial_ferry.step();

    ASSERT_EQ(updated_ferry.is_occupied_seat(Position { 0, 0 }), true);
}

TEST(FerryRulesTest, AisleStaysUnoccupied)
{
    auto const input = ".";
    Ferry initial_ferry(input);

    Ferry updated_ferry = initial_ferry.step();

    ASSERT_EQ(updated_ferry.is_occupied_seat(Position { 0, 0 }), false);
}

TEST(FerryRulesTest, TwoAislesInOneRowStayUnoccupied)
{
    auto const input = "..";
    Ferry initial_ferry(input);

    Ferry updated_ferry = initial_ferry.step();

    ASSERT_EQ(updated_ferry.is_occupied_seat(Position { 0, 0 }), false);
    ASSERT_EQ(updated_ferry.is_occupied_seat(Position { 1, 0 }), false);
}

TEST(FerryRulesTest, TwoAislesInTwoRowsStayUnoccupied)
{
    auto const input = ".\n.";
    Ferry initial_ferry(input);

    Ferry updated_ferry = initial_ferry.step();

    ASSERT_EQ(updated_ferry.is_occupied_seat(Position { 0, 0 }), false);
    ASSERT_EQ(updated_ferry.is_occupied_seat(Position { 0, 1 }), false);
}

TEST(FerryRulesTest, TwoEmptySeatsInOneRowsBecomeOccupied)
{
    auto const input = "LL";
    Ferry initial_ferry(input);
    Ferry updated_ferry = initial_ferry.step();

    ASSERT_EQ(updated_ferry.is_occupied_seat(Position { 0, 0 }), true);
    ASSERT_EQ(updated_ferry.is_occupied_seat(Position { 1, 0 }), true);
}

TEST(FerryRulesTest, TwoEmptySeatsInTwoRowsBecomeOccupied)
{
    auto const input = "L\nL";
    Ferry initial_ferry(input);
    Ferry updated_ferry = initial_ferry.step();

    ASSERT_EQ(updated_ferry.is_occupied_seat(Position { 0, 0 }), true);
    ASSERT_EQ(updated_ferry.is_occupied_seat(Position { 0, 1 }), true);
}

TEST(FerryRulesTest, OneEmptyOneOccupiedRemainsUnchanged)
{
    auto const input = "#\nL";
    Ferry initial_ferry(input);
    Ferry updated_ferry = initial_ferry.step();

    ASSERT_EQ(updated_ferry.is_occupied_seat(Position { 0, 0 }), true);
    ASSERT_EQ(updated_ferry.is_occupied_seat(Position { 0, 1 }), false);
}

TEST(FerryRulesTest, ThreeByThreeEmptySeatsGetOccupied)
{
    auto const input = "LLL\nLLL\nLLL";
    Ferry initial_ferry(input);
    Ferry updated_ferry = initial_ferry.step();
    Ferry expected_ferry { "###\n###\n###" };

    ASSERT_EQ(updated_ferry, expected_ferry);
}

// ###
// ###
// ###
//
// 353
// 585
// 353
//
// #L#
// LLL
// #L#

TEST(FerryRulesTest, ThreeByThreeFullSeats)
{
    auto const input = "###\n###\n###";
    Ferry initial_ferry(input);
    Ferry updated_ferry = initial_ferry.step();

    Ferry expected_ferry { "#L#\nLLL\n#L#" };

    ASSERT_EQ(updated_ferry, expected_ferry);
}

// ###
// #L#
// ###
//
// 353
// 585
// 353
//
// #L#
// LLL
// #L#

TEST(FerryRulesTest, ThreeByThreeFullSeatsWithEmptyCenter)
{
    auto const input = "###\n#L#\n###";
    Ferry initial_ferry(input);
    Ferry updated_ferry = initial_ferry.step();

    ASSERT_EQ(updated_ferry.get_number_of_occupied_seats(), 4U);
}

class FerryTestSpy : public Ferry {
public:
    explicit FerryTestSpy(std::string const& input)
        : Ferry(input)
    {
    }

    bool testNumberOfOccupiedNeighbors(int x, int y, int expected_number_of_neigbhors)
    {
        return getNumberOfOccupiedNeighbours(x, y) == expected_number_of_neigbhors;
    }
    bool testNeighbourSeatInDirection(int x, int y , int offset_x , int offset_y , std::string expected_seat){
        return getNeighbourSeatsInDirection(x,y,offset_x,offset_y) == expected_seat;
    }
};

TEST(FerrySeatInDirection, Spycheck){
    auto const input = "...\n"
                       ".L.\n"
                       "...";
    FerryTestSpy initial_ferry(input);
    std::string expectedStringInDirection = ".";
    ASSERT_EQ(initial_ferry.testNeighbourSeatInDirection(1,1,1,1,"."),true);
}

class FerryOccupiedNeighboursTestFixture
    : public ::testing::TestWithParam<std::pair<std::string, int>> {
};

TEST_P(FerryOccupiedNeighboursTestFixture, SpyCheck)
{
    auto const input = GetParam().first;
    FerryTestSpy initial_ferry(input);

    int expectedNumberOfNeighbours = GetParam().second;
    ASSERT_EQ(initial_ferry.testNumberOfOccupiedNeighbors(1, 1, expectedNumberOfNeighbours), true);
}

INSTANTIATE_TEST_SUITE_P(FerryOccupiedNeighboursTest, FerryOccupiedNeighboursTestFixture,
    ::testing::Values(std::make_pair("###\n"
                                     "#L#\n"
                                     "###",
                          8),
        std::make_pair("...\n"
                       ".L.\n"
                       "...",
            0),
        std::make_pair("#..\n"
                       ".L.\n"
                       "...",
            1),
        std::make_pair(".#.\n"
                       ".L.\n"
                       "...",
            1),
        std::make_pair("..#\n"
                       ".L.\n"
                       "...",
            1),
        std::make_pair("...\n"
                       "#L.\n"
                       "...",
            1),
        std::make_pair("...\n"
                       ".L#\n"
                       "...",
            1),
        std::make_pair("...\n"
                       ".L.\n"
                       "#..",
            1),
        std::make_pair("...\n"
                       ".L.\n"
                       ".#.",
            1),
        std::make_pair("...\n"
                       ".L.\n"
                       "..#",
            1),
        std::make_pair("....\n"
                       ".L.#\n"
                       "....",
            1)));
