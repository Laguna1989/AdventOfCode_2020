#include "parser.hpp"
#include <sstream>

namespace {
void removeDotAtEnd(std::string& input)
{
    if (strutil::ends_with(input, ".")) {
        input = input.substr(0, input.length() - 1);
    }
}

Token parseSingleToken(std::string const& subToken)
{
    auto const pattern = "(\\d)+ (\\w+ \\w+) bags?";
    std::regex re { pattern };
    std::smatch match;
    std::regex_search(subToken, match, re);
    return Token { match[2], std::stoul(match[1]) };
}

std::vector<Token> parseContainerTokens(std::string const& input)
{
    std::vector<Token> tokens {};
    auto tokensString = input;
    if (tokensString != "no other bags.") {
        // tokensString = "5 faded blue bags, 6 dotted black bags."
        removeDotAtEnd(tokensString);

        auto const subTokens = strutil::split(tokensString, ", ");

        for (auto const subToken : subTokens) {
            tokens.emplace_back(parseSingleToken(subToken));
        }
    }
    return tokens;
}

std::string const parseContainerIdentifier(std::string const& containerString)
{
    return containerString.substr(0, containerString.length() - 5);
}

std::vector<Container>::const_iterator findIdentifierInList(
    std::vector<Container> const& containers, std::string identifier)
{
    return std::find_if(containers.begin(), containers.end(),
        [identifier](auto const& c) { return c.identifier == identifier; });
}

} // namespace

Container parseOneLine(std::string const& input)
{
    auto const split = strutil::split(input, " contain ");
    auto const identifier = parseContainerIdentifier(split.at(0));
    std::vector<Token> const tokens = parseContainerTokens(split.at(1));
    return Container { identifier, tokens };
}

std::vector<Container> parseMultipleLines(std::string const& input)
{
    std::vector<Container> containers;

    std::stringstream ss(input);
    std::string line;
    while (std::getline(ss, line)) {
        if (line.empty()) {
            continue;
        }

        auto [identifier, tokens] = parseOneLine(line);
        containers.emplace_back(Container { identifier, tokens });
    }

    return containers;
}

std::set<std::string> listValidContainers(
    std::vector<Container> const& containers, std::string const& rootBag)
{
    std::vector<std::string> list;
    list.push_back(rootBag);

    auto index = 0;
    while (index < list.size()) {
        for (auto const& container : containers) {
            for (auto const& token : container.containedTokens) {

                std::string const tokenInContainer = token.identifier;
                if (tokenInContainer == list.at(index)) {
                    std::string candidateToBeAdded = container.identifier;
                    auto it = std::find(list.begin(), list.end(), candidateToBeAdded);
                    if (it == list.end()) {
                        list.push_back(candidateToBeAdded);
                    }
                }
            }
        }
        index++;
    }

    list.erase(std::remove(list.begin(), list.end(), rootBag), list.end());

    return std::set<std::string> { list.begin(), list.end() };
}

std::size_t neededContainersFor(std::vector<Container> const& containers, std::string const& root)
{
    if (containers.empty()) {
        return 0;
    }

    if (findIdentifierInList(containers, root) == containers.end()) {
        return 0;
    }

    std::vector<Token> tokensToCheck { Token { root, 1 } };
    std::size_t sum = 0;

    while (!tokensToCheck.empty()) {
        Token tokenToCheck = tokensToCheck.back();
        std::string identifierToCheck = tokenToCheck.identifier;
        tokensToCheck.pop_back();

        auto const it = findIdentifierInList(containers, identifierToCheck);

        if (it == containers.end()) {
            continue;
        }

        for (auto const& containedToken : it->containedTokens) {
            Token token{containedToken.identifier, containedToken.count * tokenToCheck.count};
            tokensToCheck.push_back(token);
            sum += containedToken.count * tokenToCheck.count;
        }
    }

    return sum;
}
