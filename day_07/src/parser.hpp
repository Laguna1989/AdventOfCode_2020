#ifndef CODE_KATA_PARSER_HPP
#define CODE_KATA_PARSER_HPP

#include "strutils.hpp"
#include <iostream>
#include <regex>
#include <set>
#include <string>
#include <tuple>
#include <vector>

// TODO rename
struct Token {
    std::string identifier;
    std::size_t count;
};

struct Container {
    std::string identifier;
    std::vector<Token> containedTokens;
};

std::set<std::string> listValidContainers(
    std::vector<Container> const& containers, std::string const& rootBag);

Container parseOneLine(std::string const& input);
std::vector<Container> parseMultipleLines(std::string const& input);

std::size_t neededContainersFor(std::vector<Container> const& containers, std::string const& root);

#endif // CODE_KATA_PARSER_HPP
