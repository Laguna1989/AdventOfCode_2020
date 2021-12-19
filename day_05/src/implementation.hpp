#ifndef IMPLEMENTATION_HPP_GUARD
#define IMPLEMENTATION_HPP_GUARD

#include <string>
#include <tuple>

std::tuple<std::string, std::string> splitStringIntoRowsAndColumn(std::string const& input);
int GetRowNumber(std::string const& input);
int GetColumnNumber(std::string const& input);

int GetSeatID(int row, int seat);

int GetSeatIdFromString(std::string const& input);
#endif
