#ifndef ADVENTOFCODE2020_IMPLEMENTATION_HPP
#define ADVENTOFCODE2020_IMPLEMENTATION_HPP

#include <cstdint>
#include <string>
#include <vector>

std::vector<std::uint64_t> convertToVector(std::string const& input);

std::uint64_t calculateProductOfOneAndThreeJoltDiffString(std::string const& input);

std::vector<std::uint64_t> sortAndCalculateDifferencesOfNumbers(
    std::vector<std::uint64_t> const& numbers);

std::uint64_t getNumberOfOnesFromDifferences(std::vector<std::uint64_t> const& differences);
std::uint64_t getNumberOfThreesFromDifferences(std::vector<std::uint64_t> const& differences);

#endif // ADVENTOFCODE2020_IMPLEMENTATION_HPP
