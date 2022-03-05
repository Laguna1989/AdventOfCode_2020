
#include <ferry.hpp>
#include <gtest/gtest.h>

class FerryTestSpy : public Ferry {
public:
    explicit FerryTestSpy(std::string const& input)
        : Ferry(input)
    {
    }

    void testNumberOfOccupiedNeighbors(int x, int y, int expected_number_of_neigbhors) const
    {
        ASSERT_EQ(getNumberOfOccupiedNeighbours(x, y), expected_number_of_neigbhors);
    }
    void testNeighbourSeatInDirection(
        int x, int y, int offset_x, int offset_y, std::string expected_seat) const
    {
        ASSERT_EQ(getNeighbourSeatsInDirection(x, y, offset_x, offset_y), expected_seat);
    }
};

struct DirectionTestData {
    std::string input;
    int x_offset, y_offset;
};
class FerryOccupiedNeighboursInDirectionTestFixture
    : public ::testing::TestWithParam<std::pair<struct DirectionTestData, std::string>> {
};

TEST_P(FerryOccupiedNeighboursInDirectionTestFixture, CorrectResult)
{
    auto const input = GetParam().first;
    FerryTestSpy const initial_ferry(input.input);

    auto const expectedNeighbor = GetParam().second;
    initial_ferry.testNeighbourSeatInDirection(
        1, 1, input.x_offset, input.y_offset, expectedNeighbor),
        true;
}

INSTANTIATE_TEST_SUITE_P(FerryDirectionNeighboursTest,
    FerryOccupiedNeighboursInDirectionTestFixture,
    ::testing::Values(std::make_pair(DirectionTestData { "###\n"
                                                         "#L#\n"
                                                         "###\n",
                                         1, 1 },
                          "#"),
        std::make_pair(DirectionTestData { "...\n"
                                           ".L.\n"
                                           "...\n"
                                           ".#.",
                           0, 1 },
            "#")));

class FerryOccupiedNeighboursTestFixture
    : public ::testing::TestWithParam<std::pair<std::string, int>> {
};

TEST_P(FerryOccupiedNeighboursTestFixture, CorrectResult)
{
    auto const input = GetParam().first;
    FerryTestSpy const initial_ferry(input);

    int const expectedNumberOfNeighbours = GetParam().second;
    initial_ferry.testNumberOfOccupiedNeighbors(1, 1, expectedNumberOfNeighbours), true;
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
