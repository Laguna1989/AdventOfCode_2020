#include "ferry.hpp"
#include "strutils.hpp"
#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>

Ferry::Ferry(std::string const& input)
    : m_representation { input }
{
    strutil::trim(m_representation);
    m_number_of_rows
        = static_cast<int>(std::count(m_representation.begin(), m_representation.end(), '\n') + 1);
    calculate_row_length();
    strutil::replace_all(m_representation, "\n", "");
}
void Ferry::calculate_row_length()
{
    if (strutil::contains(m_representation, '\n')) {
        auto const firstLineBreakPosition
            = std::find(m_representation.begin(), m_representation.end(), '\n');
        m_row_length = static_cast<int>(firstLineBreakPosition - m_representation.begin());
    } else {
        m_row_length = static_cast<int>(m_representation.size());
    }
}

int calculate_index(Position const& p, int stride)
{
    if (p.x < 0 || p.y < 0 || p.x >= stride) {
        return -1;
    }

    return p.x + p.y * stride;
}

bool Ferry::is_seat(Position const& position) const
{
    int index = calculate_index(position, m_row_length);

    return is_seat(index);
}

bool Ferry::is_seat(int index) const
{
    if (index < 0 || index >= static_cast<int>(m_representation.size()))
        return false;

    return (m_representation.at(index) != '.');
}

int Ferry::get_number_of_occupied_seats()
{
    return static_cast<int>(std::count(m_representation.begin(), m_representation.end(), '#'));
}

bool Ferry::is_occupied_seat(const Position& position) const
{
    int index = calculate_index(position, m_row_length);

    return is_occupied_seat(index);
}

bool Ferry::is_occupied_seat(int index) const
{
    if (index < 0 || index >= static_cast<int>(m_representation.size())) {
        return false;
    }
    return (m_representation.at(index) == '#');
}

std::string Ferry::getNewSeat(Position const& position) const
{
    auto numberOfOccupiedNeighbours = getNumberOfOccupiedNeighbours(position.x, position.y);

    if (is_occupied_seat(position)) {
        if (numberOfOccupiedNeighbours >= 5) {
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

Ferry Ferry::step() const
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

int Ferry::getNumberOfOccupiedNeighbours(int x, int y) const
{
    // clang-format off
    std::vector<Position> const neighborPositions {
        Position { -1, -1 },
        Position { 0, -1 },
        Position { 1, -1 },

        Position { -1, 0 },
        Position { 1, 0 },

        Position { -1, 1 },
        Position { 0, 1 },
        Position { 1, 1 } };
    // clang-format on

    return static_cast<int>(std::count_if(
        neighborPositions.begin(), neighborPositions.end(), [this, x, y](Position const& p) {
            auto representation = getNeighbourSeatsInDirection(x, y, p.x, p.y);
            return representation == "#";
        }));
}

std::string Ferry::getNeighbourSeatsInDirection(int x, int y, int x_offset, int y_offset) const
{
    std::string seat_representation = ".";
    while (true) {
        y += y_offset;
        x += x_offset;
        if (y >= m_number_of_rows || x >= m_row_length) {
            return seat_representation;
        }
        auto const index = calculate_index(Position { x, y }, m_row_length);
        if (index < 0) {
            return seat_representation;
        }
        if (!is_seat(index)) {
            continue;
        }
        return std::string { m_representation[index] };
    }
}

bool Ferry::operator==(Ferry const& other) const
{
    return (m_number_of_rows == other.m_number_of_rows)
        && (m_representation == other.m_representation);
}
