#ifndef IMPLEMENTATION_HPP_GUARD
#define IMPLEMENTATION_HPP_GUARD

#include <string>
#include <vector>

std::vector<std::uint64_t> splitAndConvertToNumbers(std::string const& input);

std::vector<std::uint64_t> getPreamble(
    std::vector<std::uint64_t> const& vector, int preamble_size, std::size_t currentIndexToCheck);

bool numberCanBeConstructedFromPreamble(
    std::vector<std::uint64_t> const& preamble, std::uint64_t currentNumberToCheck);

std::uint64_t findFirstIllegalNumberInVector(
    std::vector<std::uint64_t> const& vector, int preamble_size);

std::uint64_t findFirstIllegalNumberInString(std::string const& input, int preamble_size);

std::uint64_t findSumOfEnclosingArrayInVector(
    std::vector<std::uint64_t> const& vector, std::uint64_t invalidNumber);

std::uint64_t findSumOfEnclosingArrayInString(
    std::string const& input, std::uint64_t invalidNumber);

#endif
