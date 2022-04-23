#ifndef ADVENTOFCODE2020_FERRY_HPP
#define ADVENTOFCODE2020_FERRY_HPP

#include "position.hpp"
#include <cstdint>
#include <string>
#include <vector>

class Ferry {
public:
    explicit Ferry(std::string const& input);
    virtual ~Ferry() = default;

    bool is_seat(Position const& p) const;
    bool is_occupied_seat(const Position& position) const;

    int get_number_of_occupied_seats();

    Ferry step();
    bool operator==(Ferry const& other) const;

    std::string getNeighbourSeatsInDirection(int x, int y, int offset_x, int offset_y) const;

protected:
    int getNumberOfOccupiedNeighbours(int x, int y) const;

private:
    std::string m_representation {};
    int m_row_length { 100000 };
    void calculate_row_length();

    bool is_seat(int index) const;
    bool is_occupied_seat(int index) const;

    int m_number_of_rows { 10000 };
    std::string getNewSeat(Position const& position);
};

#endif // ADVENTOFCODE2020_FERRY_HPP
