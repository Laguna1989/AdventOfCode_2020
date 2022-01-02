#include "implementation.hpp"
#include "strutils.hpp"
#include <algorithm>
#include <iostream>
#include <numeric>

std::vector<uint64_t> convertToVector(std::string const& input)
{
    auto const strings = strutil::split(input, "\n");
    std::vector<std::uint64_t> numbers {};
    numbers.resize(strings.size());

    std::transform(strings.begin(), strings.end(), numbers.begin(),
        [](auto const& str) { return std::stoul(str); });

    return numbers;
}

std::uint64_t calculateProductOfOneAndThreeJoltDiffString(std::string const& input)
{
    auto const numbers = convertToVector(input);
    auto const differences = sortAndCalculateDifferencesOfNumbers(numbers);

    return getNumberOfOnesFromDifferences(differences)
        * getNumberOfThreesFromDifferences(differences);
}

std::vector<std::uint64_t> sortAndCalculateDifferencesOfNumbers(
    std::vector<std::uint64_t> const& numbers)
{
    std::vector<std::uint64_t> copy { numbers };
    std::sort(copy.begin(), copy.end());

    std::vector<std::uint64_t> differences;
    differences.resize(copy.size());
    std::adjacent_difference(copy.begin(), copy.end(), differences.begin());

    // Add jolt conversion from last converter to device
    differences.push_back(3);
    return differences;
}

std::uint64_t getNumberOfOnesFromDifferences(std::vector<std::uint64_t> const& differences)
{
    return std::count_if(
        differences.begin(), differences.end(), [](auto const& n) { return n == 1; });
}

std::uint64_t getNumberOfThreesFromDifferences(std::vector<std::uint64_t> const& differences)
{
    return std::count_if(
        differences.begin(), differences.end(), [](auto const& n) { return n == 3; });
}

// std::vector<std::uint64_t> const {0, 1, 4, 5, 6, 7, 10, 11, 12, 15, 16, 19, (22)};
// std::vector<std::uint64_t> const { 1,  3, 1, 1, 1, 3,  1,  1,  3,  1,  3, 3 };
// all of them                                -> 1
// 1 group of 3 ones  -> all three, two, one  -> 3 = n
// 1 group of 2 ones -> both or one of them   -> 2 = m
// combination of groups                        -> (n-1) * (m-1) = 2 * 1 = 2

std::uint64_t calculateNumberOfCombinationsForDifferences(std::vector<std::uint64_t> const& input)
{
    return 8;
}

std::uint64_t calculateNumberOfSpecificOnePermutations(
    std::vector<std::uint64_t> const& input, std::uint64_t groupSize)
{
    std::uint64_t sum = 0u;
    for (auto i = 0u; i != input.size() - groupSize; ++i) {
        auto const valueAtI = input.at(i);
        bool found { true };
        for (auto j = i + 1; j != i + groupSize; ++j) {

            auto const valueAtJ = input.at(j);

            auto const currentMatching = valueAtJ == valueAtI;
            std::cout << i << " " << j << " " << valueAtI << " " << valueAtJ << " "
                      << std::boolalpha << found << " " << currentMatching << std::endl;
            found = found && currentMatching;
        }
        std::cout << std::endl;
        if (found) {
            sum++;
        }
    }
    return sum;
}
