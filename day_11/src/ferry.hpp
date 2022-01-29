#ifndef ADVENTOFCODE2020_FERRY_HPP
#define ADVENTOFCODE2020_FERRY_HPP

#include "position.hpp"
#include <cstdint>
#include <string>
#include <vector>

class Ferry {
public:
    Ferry(std::string const& input);

    bool is_seat(Position const& p);

    int get_number_of_occupied_seats();

    bool is_occupied_seat(Position position);

    Ferry step();

private:
    std::string m_representation {};
    int m_rowLength { 0 };
    void calculate_row_length();
};

#endif // ADVENTOFCODE2020_FERRY_HPP
