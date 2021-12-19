#include "split_input_into_groups.hpp"
#include <regex>

std::vector<std::string> splitInputIntoGroups(std::string const& input)
{
    if (input.empty()) {
        return {};
    }

    std::vector<std::string> result;
    std::regex const regex { "\n\n" };
    std::sregex_token_iterator iter(input.begin(), input.end(), regex, -1);

    for (std::sregex_token_iterator end; iter != end; ++iter) {
        result.emplace_back(iter->str());
    }

    return result;
}
