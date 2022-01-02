#ifndef ADVENTOFCODE2020_IMPLEMENTATION_HPP
#define ADVENTOFCODE2020_IMPLEMENTATION_HPP

#include <cstdint>
#include <string>
#include <vector>

std::vector<std::uint64_t> convertToVector(std::string const& input);

std::uint64_t calculateProductOfOneAndThreeJoltDiffString(std::string const& input);

std::vector<std::uint64_t> calculateDifferencesOfSortedNumbers(
    std::vector<std::uint64_t> const& numbers);

#endif // ADVENTOFCODE2020_IMPLEMENTATION_HPP
