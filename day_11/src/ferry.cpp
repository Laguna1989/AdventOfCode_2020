#include "ferry.hpp"
#include "strutils.hpp"
#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>

Ferry::Ferry(std::string const& input)
    : m_representation { input }
{
}

bool Ferry::is_seat(Position const& p) {
    int index = p.x;

    return (m_representation[index] != '.');
}
