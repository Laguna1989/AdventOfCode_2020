#include "landscape.hpp"
#include <algorithm>

Landscape::Landscape(std::string const& input)
    : m_input(input)
{
    m_sizeX = getSizeX();
    m_sizeY = getSizeY();
    m_input.erase(std::remove(m_input.begin(), m_input.end(), '\n'), m_input.end());
}

size_t Landscape::getSizeY() const
{
    return std::count(m_input.cbegin(), m_input.cend(), '\n') + 1;
}

size_t Landscape::getSizeX() const
{
    return std::distance(m_input.cbegin(), std::find(m_input.cbegin(), m_input.cend(), '\n'));
}

std::size_t Landscape::indexFromPosition(Position const& position) const
{
    std::size_t xPos = position.xPos % m_sizeX;

    return xPos + position.yPos * m_sizeX;
}

bool Landscape::hasTreeAt(Position const& p) const
{
    std::size_t const index = indexFromPosition(p);
    return m_input.at(index) == '#';
}

std::size_t Landscape::sizeX() const { return m_sizeX; }

std::size_t Landscape::sizeY() const { return m_sizeY; }

std::size_t Landscape::countTrees(Position const& p) const
{
    std::size_t currentXPos = 0;
    std::size_t currentYPos = 0;
    std::size_t numberOfTrees = 0;

    while (currentYPos < m_sizeY) {
        if (hasTreeAt(Position { currentXPos, currentYPos })) {
            ++numberOfTrees;
        }

        currentXPos += p.xPos;
        currentYPos += p.yPos;
    }

    return numberOfTrees;
}
