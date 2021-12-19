#ifndef CODE_KATA_LANDSCAPE_HPP
#define CODE_KATA_LANDSCAPE_HPP

#include "position.hpp"
#include "slope.hpp"
#include <string>

class Landscape {
public:
    Landscape(std::string const& input);

    std::size_t sizeX() const;
    std::size_t sizeY() const;

    bool hasTreeAt(Position const& p) const;

    std::size_t countTrees(Slope const& p) const;

private:
    std::string m_input;
    std::size_t m_sizeX;
    std::size_t m_sizeY;

    size_t getSizeX() const;
    size_t getSizeY() const;
    std::size_t indexFromPosition(Position const& position) const;
};

#endif // CODE_KATA_LANDSCAPE_HPP
