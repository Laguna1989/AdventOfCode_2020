#include "implementation.hpp"
#include "strutils.hpp"

std::vector<int> splitAndConvertToNumbers(std::string const& input)
{
    if (input.empty()) {
        return {};
    }

    std::vector<std::string> lines = strutil::split(input, "\n");

    std::vector<int> output;
    output.resize(lines.size());
    std::transform(
        lines.begin(), lines.end(), output.begin(), [](auto const& str) { return std::stoi(str); });

    return output;
}

std::vector<int> getPreamble(
    const std::vector<int>& vector, int preamble_size, std::size_t currentIndexToCheck)
{
    if (preamble_size > currentIndexToCheck) {
        throw std::invalid_argument { "Out of bounds" };
    }

    std::vector<int> preamble(
        vector.begin() + currentIndexToCheck - preamble_size, vector.begin() + currentIndexToCheck);

    return preamble;
}

bool numberCanBeConstructedFromPreamble(std::vector<int> const& preamble, int currentNumberToCheck)
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

int findFirstIllegalNumberInVector(std::vector<int> const& vector, int preamble_size)
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

int findFirstIllegalNumberInString(std::string const& input, int preamble_size)
{
    std::vector<int> const numbers = splitAndConvertToNumbers(input);

    return findFirstIllegalNumberInVector(numbers, preamble_size);
}
