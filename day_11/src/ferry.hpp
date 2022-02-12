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
    bool is_occupied_seat(Position position);

    int get_number_of_occupied_seats();

    Ferry step();
    bool operator==(Ferry const& other) const;

private:
    std::string m_representation {};
    int m_row_length { 100000 };
    void calculate_row_length();

    bool is_seat(int index);
    bool is_occupied_seat(int index);
    int m_number_of_rows { 10000 };
    int getNumberOfOccupiedNeighbours(int x, int y);
    std::string getNewSeat(Position const& position);
};

#endif // ADVENTOFCODE2020_FERRY_HPP
