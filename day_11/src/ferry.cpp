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

bool Ferry::is_seat(Position const& p)
{
    int index = p.x + p.y * m_rowLength;
    std::cout << "index: " << index << " row len: " << m_rowLength << "\n";
    return (m_representation[index] != '.');
}

int Ferry::get_number_of_occupied_seats()
{
    return std::count(m_representation.begin(), m_representation.end(), '#');
}
bool Ferry::is_occupied_seat(Position position) { return false; }
