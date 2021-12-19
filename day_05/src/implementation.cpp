#include "implementation.hpp"
#include <bitset>
#include <string>
#include <tuple>

std::tuple<std::string, std::string> splitStringIntoRowsAndColumn(std::string const& input)
{
    auto const row = input.substr(0, 7);
    auto const seat = input.substr(7);
    return std::make_tuple(row, seat);
}

int GetRowNumber(std::string const& input)
{
    std::bitset<7> bitset { input, 0, 7, 'F', 'B' };
    return static_cast<int>(bitset.to_ulong());
}

int GetColumnNumber(std::string const& input)
{
    std::bitset<3> bitset { input, 0, 3, 'L', 'R' };
    return static_cast<int>(bitset.to_ulong());
}

int GetSeatID(int row, int seat) { return row * 8 + seat; }

int GetSeatIdFromString(std::string const& input)
{
    int const expectedSeatID = 567;

    auto [row, column] = splitStringIntoRowsAndColumn(input);
    auto const rowNumber = GetRowNumber(row);
    auto const columnNumber = GetColumnNumber(column);

    return GetSeatID(rowNumber, columnNumber);
}
