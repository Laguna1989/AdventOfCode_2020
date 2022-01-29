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

int calculate_index(Position const& p, int stride) { return p.x + p.y * stride; }

bool Ferry::is_seat(Position const& position)
{
    int index = calculate_index(position, m_row_length);

    return is_seat(index);
}

bool Ferry::is_seat(int index) { return (m_representation.at(index) != '.'); }

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

Ferry Ferry::step()
{
    std::string updatedString = "";

    for (auto x = 0; x != m_row_length; ++x) {
        for (auto y = 0; y != m_number_of_rows; ++y) {
            Position current_position { x, y };
            if (!is_seat(current_position)) {
                updatedString += ".";
            } else {
                auto is_left_seat_occupied = is_occupied_seat(Position { x - 1, y });
                auto is_right_seat_occupied = is_occupied_seat(Position { x + 1, y });
                if (is_left_seat_occupied || is_right_seat_occupied) {
                    updatedString += "L";
                } else {
                    updatedString += "#";
                }
            }
        }
        updatedString += "\n";
    }
    updatedString.pop_back();

    return Ferry { updatedString };

    for (int i = 0; i != m_representation.size(); ++i) {
        if (!is_seat(i)) {
            updatedString += ".";
        } else {
            auto is_left_seat_occupied = is_occupied_seat(i - 1);
            auto is_right_seat_occupied = is_occupied_seat(i + 1);
            if (is_left_seat_occupied || is_right_seat_occupied) {
                updatedString += "L";
            } else {
                updatedString += "#";
            }
        }
        updatedString += "\n";
    }
    return Ferry { updatedString };
}
