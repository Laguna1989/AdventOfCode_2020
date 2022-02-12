#include "ferry.hpp"
#include "strutils.hpp"
#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>

Ferry::Ferry(std::string const& input)
    : m_representation { input }
{
    m_number_of_rows = std::count(m_representation.begin(), m_representation.end(), '\n') + 1;
    calculate_row_length();
    strutil::replace_all(m_representation, "\n", "");
}
void Ferry::calculate_row_length()
{
    if (strutil::contains(m_representation, '\n')) {
        auto const firstLineBreakPosition
            = std::find(m_representation.begin(), m_representation.end(), '\n');
        m_row_length = firstLineBreakPosition - m_representation.begin();
    } else {
        m_row_length = m_representation.size();
    }
}

int calculate_index(Position const& p, int stride)
{
    if (p.x < 0 || p.y < 0 || p.x >= stride) {
        return -1;
    }

    return p.x + p.y * stride;
}

bool Ferry::is_seat(Position const& position)
{
    int index = calculate_index(position, m_row_length);

    return is_seat(index);
}

bool Ferry::is_seat(int index)
{
    if (index < 0 || index >= m_representation.size())
        return false;

    return (m_representation.at(index) != '.');
}

int Ferry::get_number_of_occupied_seats()
{
    return std::count(m_representation.begin(), m_representation.end(), '#');
}

bool Ferry::is_occupied_seat(Position position)
{
    int index = calculate_index(position, m_row_length);

    return is_occupied_seat(index);
}

bool Ferry::is_occupied_seat(int index)
{
    if (index < 0 || index >= m_representation.size()) {
        return false;
    }
    return (m_representation.at(index) == '#');
}

std::string Ferry::getNewSeat(Position const& position)
{
    auto numberOfOccupiedNeighbours = getNumberOfOccupiedNeighbours(position.x, position.y);

    if (is_occupied_seat(position)) {
        if (numberOfOccupiedNeighbours >= 4) {
            return "L";
        } else {
            return "#";
        }
    } else {
        if (numberOfOccupiedNeighbours == 0) {
            return "#";
        } else {
            return "L";
        }
    }
}

Ferry Ferry::step()
{
    std::string updatedString = "";
    for (auto y = 0; y != m_number_of_rows; ++y) {
        for (auto x = 0; x != m_row_length; ++x) {
            Position current_position { x, y };
            if (!is_seat(current_position)) {
                updatedString += ".";
                continue;
            }

            updatedString += getNewSeat(current_position);
        }
        updatedString += "\n";
    }
    updatedString.pop_back();

    return Ferry { updatedString };
}

int Ferry::getNumberOfOccupiedNeighbours(int x, int y)
{
    std::vector<Position> const neighborPositions { Position { x - 1, y - 1 },
        Position { x, y - 1 }, Position { x + 1, y - 1 }, Position { x - 1, y },
        Position { x + 1, y }, Position { x - 1, y + 1 }, Position { x, y + 1 },
        Position { x + 1, y + 1 } };

    return static_cast<int>(std::count_if(neighborPositions.begin(), neighborPositions.end(),
        [this](Position const& p) { return is_occupied_seat(p); }));
}

bool Ferry::operator==(Ferry const& other) const
{

    return (m_representation == other.m_representation)
        && (m_number_of_rows == other.m_number_of_rows);
}
