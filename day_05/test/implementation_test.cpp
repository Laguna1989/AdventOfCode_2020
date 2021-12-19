#include "example_input.hpp"
#include "implementation.hpp"
#include "gtest/gtest.h"
#include <algorithm>
#include <sstream>
#include <string>
#include <tuple>

using namespace ::testing;

class SplitStringTestFixture
    : public ::testing::TestWithParam<std::tuple<std::string, std::string, std::string>> {
};

TEST_P(SplitStringTestFixture, CorrectRow)
{
    std::string input = std::get<0>(GetParam());
    std::string expectedResult = std::get<1>(GetParam());
    auto [row, _] = splitStringIntoRowsAndColumn(input);

    EXPECT_EQ(row, expectedResult);
}

TEST_P(SplitStringTestFixture, CorrectSeat)
{
    std::string input = std::get<0>(GetParam());
    std::string expectedResult = std::get<2>(GetParam());
    auto [_, seat] = splitStringIntoRowsAndColumn(input);

    EXPECT_EQ(seat, expectedResult);
}

INSTANTIATE_TEST_SUITE_P(SplitStringTest, SplitStringTestFixture,
    ::testing::Values(std::make_tuple("FFFFFFFLLL", "FFFFFFF", "LLL"),
        std::make_tuple("BBBBBBBLLL", "BBBBBBB", "LLL"),
        std::make_tuple("FFFFFFFRRR", "FFFFFFF", "RRR")));

class RowNumberTestFixture : public ::testing::TestWithParam<std::tuple<std::string, int>> {
};

TEST_P(RowNumberTestFixture, CorrectRow)
{
    std::string input = std::get<0>(GetParam());
    int row = GetRowNumber(input);
    int expectedRow = std::get<1>(GetParam());

    EXPECT_EQ(row, expectedRow);
}

INSTANTIATE_TEST_SUITE_P(RowNumberTest, RowNumberTestFixture,
    ::testing::Values(std::make_tuple("FFFFFFF", 0), std::make_tuple("BBBBBBB", 127),
        std::make_tuple("FFFFFFB", 1), std::make_tuple("FFFFFBF", 2),
        std::make_tuple("FFFBFFF", 8)));

class SeatNumberTestFixture : public ::testing::TestWithParam<std::tuple<std::string, int>> {
};

TEST_P(SeatNumberTestFixture, CorrectSeat)
{
    std::string input = std::get<0>(GetParam());
    int seat = GetColumnNumber(input);
    int expectedSeat = std::get<1>(GetParam());

    EXPECT_EQ(seat, expectedSeat);
}

INSTANTIATE_TEST_SUITE_P(SeatNumberTest, SeatNumberTestFixture,
    ::testing::Values(std::make_tuple("LLL", 0), std::make_tuple("LLR", 1),
        std::make_tuple("LRL", 2), std::make_tuple("LRR", 3), std::make_tuple("RLL", 4),
        std::make_tuple("RLR", 5), std::make_tuple("RRL", 6), std::make_tuple("RRR", 7)));

class SeatIdTestFixture : public ::testing::TestWithParam<std::tuple<int, int, int>> {
};

TEST_P(SeatIdTestFixture, GetCorrectSeatID)
{
    int row = std::get<0>(GetParam());
    int seat = std::get<1>(GetParam());
    int expectedSeatID = std::get<2>(GetParam());

    int seatID = GetSeatID(row, seat);

    EXPECT_EQ(seatID, expectedSeatID);
}

INSTANTIATE_TEST_SUITE_P(SeatIdTest, SeatIdTestFixture,
    ::testing::Values(std::make_tuple(0, 0, 0), std::make_tuple(0, 1, 1), std::make_tuple(1, 1, 9),
        std::make_tuple(44, 5, 357)));

class BossMonsterTestFixture : public ::testing::TestWithParam<std::tuple<std::string, int>> {
};

TEST_P(BossMonsterTestFixture, ExamplesFromReadme)
{
    std::string const input = std::get<0>(GetParam());

    int const expectedSeatID = std::get<1>(GetParam());
    auto seatID = GetSeatIdFromString(input);

    ASSERT_EQ(seatID, expectedSeatID);
}

INSTANTIATE_TEST_SUITE_P(BossMonsterTest, BossMonsterTestFixture,
    ::testing::Values(std::make_tuple("BFFFBBFRRR", 567), std::make_tuple("FFFBBBFRRR", 119),
        std::make_tuple("BBFFBBFRLL", 820)));

auto getSeatIDs()
{
    std::stringstream stream { example_input };
    std::vector<int> seatIDs;
    while (!stream.eof()) {
        std::string input;
        stream >> input;
        seatIDs.emplace_back(GetSeatIdFromString(input));
    }
    return seatIDs;
}

TEST(BossMonsterTest, UseExampleInputPart1)
{
    std::vector<int> seatIDs = getSeatIDs();

    auto max = *std::max_element(seatIDs.cbegin(), seatIDs.cend());
    ASSERT_EQ(max, 888);
}

TEST(BossMonsterTest, UseExampleInputPart2)
{
    std::vector<int> seatIDs = getSeatIDs();
    std::sort(seatIDs.begin(), seatIDs.end());

    int lastSeatID = seatIDs.front();

    for (int currentSeatID : seatIDs) {
        if (currentSeatID > lastSeatID + 1) {
            std::cout << "Our seat ID is: " << currentSeatID - 1 << std::endl;
            break;
        }
        lastSeatID = currentSeatID;
    }

    ASSERT_EQ(lastSeatID + 1, 522);
}
