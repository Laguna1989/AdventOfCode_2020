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

private:
    std::string m_representation {};
};

#endif // ADVENTOFCODE2020_FERRY_HPP
