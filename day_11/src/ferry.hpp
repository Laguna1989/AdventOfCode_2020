#ifndef ADVENTOFCODE2020_FERRY_HPP
#define ADVENTOFCODE2020_FERRY_HPP

#include "position.hpp"
#include <cstdint>
#include <string>
#include <vector>

class Ferry {
public:
    explicit Ferry(std::string const& input);

    bool is_seat(Position const& p);

    int get_number_of_occupied_seats();

    bool is_occupied_seat(Position position);

    Ferry step();

private:
    std::string m_representation {};
    int m_row_length { 100000 };
    void calculate_row_length();

    bool is_seat(int index);
    bool is_occupied_seat(int index);
    int m_number_of_rows { 10000 };
};

#endif // ADVENTOFCODE2020_FERRY_HPP
