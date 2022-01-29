#include "ferry.hpp"
#include "strutils.hpp"
#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>

Ferry::Ferry(std::string const& input)
    : m_representation { input }
{
    calculate_row_length();
}
void Ferry::calculate_row_length()
{
    if (strutil::contains(m_representation, '\n')) {
        auto const firstLineBreakPosition
            = std::find(m_representation.begin(), m_representation.end(), '\n');
        m_rowLength = firstLineBreakPosition - m_representation.begin();
    }

    strutil::replace_all(m_representation, "\n", "");
}

int calculate_index(Position const& p, int stride) { return p.x + p.y * stride; }

bool Ferry::is_seat(Position const& position)
{
    int index = calculate_index(position, m_rowLength);

    return (m_representation[index] != '.');
}

int Ferry::get_number_of_occupied_seats()
{
    return std::count(m_representation.begin(), m_representation.end(), '#');
}
bool Ferry::is_occupied_seat(Position position)
{
    int index = calculate_index(position, m_rowLength);

    return (m_representation[index] == '#');
}

Ferry Ferry::step()
{

    for (int i = 0; i != m_representation.size(); ++i) {
        auto current_object = m_representation.at(i);
        if (current_object == '.') {
            return Ferry { "." };
        } else {
            return Ferry { "#" };
        }
    }
}
