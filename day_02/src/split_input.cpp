#include "split_input.hpp"

std::tuple<std::string, std::string> split_input(std::string const& input)
{
    std::string const delimiter = ": ";
    auto split_pos = input.find(delimiter);
    auto const policy = input.substr(0, split_pos);
    auto const password = input.substr(split_pos + delimiter.length());

    return std::make_tuple(policy, password);
}
