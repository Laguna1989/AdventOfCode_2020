#include "implementation.hpp"
#include "strutils.hpp"
#include <iostream>
#include <sstream>

std::vector<std::uint64_t> splitAndConvertToNumbers(std::string const& input)
{
    if (input.empty()) {
        return {};
    }

    std::vector<std::string> lines = strutil::split(input, "\n");

    std::vector<std::uint64_t> output;
    output.resize(lines.size());
    std::transform(lines.begin(), lines.end(), output.begin(), [](auto const& str) {
        std::stringstream ss { str };
        std::uint64_t number;
        ss >> number;
        return number;
    });

    return output;
}

std::vector<std::uint64_t> getPreamble(
    const std::vector<std::uint64_t>& vector, int preamble_size, std::size_t currentIndexToCheck)
{
    if (preamble_size > currentIndexToCheck) {
        throw std::invalid_argument { "Out of bounds" };
    }

    std::vector<std::uint64_t> preamble(
        vector.begin() + currentIndexToCheck - preamble_size, vector.begin() + currentIndexToCheck);

    return preamble;
}

bool numberCanBeConstructedFromPreamble(
    std::vector<std::uint64_t> const& preamble, std::uint64_t currentNumberToCheck)
{
    for (auto indexA = 0U; indexA != preamble.size() - 1; ++indexA) {
        for (auto indexB = indexA + 1; indexB != preamble.size(); ++indexB) {
            auto const valA = preamble.at(indexA);
            auto const valB = preamble.at(indexB);
            if (valA + valB == currentNumberToCheck) {
                return true;
            }
        }
    }

    return false;
}

std::uint64_t findFirstIllegalNumberInVector(
    std::vector<std::uint64_t> const& vector, int preamble_size)
{
    for (std::size_t currentIndexToCheck = preamble_size; currentIndexToCheck != vector.size();
         ++currentIndexToCheck) {
        int currentNumberToCheck = vector.at(currentIndexToCheck);

        auto const currentPreamble = getPreamble(vector, preamble_size, currentIndexToCheck);

        if (!numberCanBeConstructedFromPreamble(currentPreamble, currentNumberToCheck)) {
            return currentNumberToCheck;
        }
    }

    return 0;
}

std::uint64_t findFirstIllegalNumberInString(std::string const& input, int preamble_size)
{
    std::vector<std::uint64_t> const numbers = splitAndConvertToNumbers(input);

    return findFirstIllegalNumberInVector(numbers, preamble_size);
}

std::uint64_t findSumOfEnclosingArrayInString(std::string const& input, std::uint64_t invalidNumber)
{
    std::vector<std::uint64_t> const numbers = splitAndConvertToNumbers(input);
    return findSumOfEnclosingArrayInVector(numbers, invalidNumber);
}

std::uint64_t findSumOfEnclosingArrayInVector(
    std::vector<std::uint64_t> const& vector, std::uint64_t invalidNumber)
{
    for (std::size_t i = 0U; i != vector.size() - 1; ++i) {
        if (i == vector.size() - 2) {
            break;
        }
        std::uint64_t currentSum = vector.at(i);
        for (std::size_t j = i + 1; j != vector.size(); ++j) {
            currentSum += vector.at(j);

            if (currentSum == invalidNumber) {
                auto preamble = getPreamble(vector, j - i + 1, j + 1);
                auto minElement = *std::min_element(preamble.begin(), preamble.end());
                auto maxElement = *std::max_element(preamble.begin(), preamble.end());

                return minElement + maxElement;
            }
        }
    }

    return 0;
}
