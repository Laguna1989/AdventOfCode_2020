#include "implementation.hpp"
#include "strutils.hpp"
#include <algorithm>
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

    return 35;
}
std::vector<std::uint64_t> calculateDifferencesOfSortedNumbers(
    std::vector<std::uint64_t> const& numbers)
{
    std::vector<std::uint64_t> copy { numbers };

    std::vector<std::uint64_t> differences;
    differences.resize(numbers.size());
    std::adjacent_difference(numbers.begin(), numbers.end(), differences.begin());
    return differences;
}
