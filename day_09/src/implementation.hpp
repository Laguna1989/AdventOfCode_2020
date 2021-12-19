#ifndef IMPLEMENTATION_HPP_GUARD
#define IMPLEMENTATION_HPP_GUARD

#include <string>
#include <vector>

std::vector<int> splitAndConvertToNumbers(std::string const& input);
std::vector<int> getPreamble(
    std::vector<int> const& vector, int preamble_size, std::size_t currentIndexToCheck);
bool numberCanBeConstructedFromPreamble(std::vector<int> const& preamble, int currentNumberToCheck);
int findFirstIllegalNumberInVector(std::vector<int> const& vector, int preamble_size);
int findFirstIllegalNumberInString(std::string const& input, int preamble_size);

#endif
