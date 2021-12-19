#include "is_password_correct.hpp"
#include <regex>

struct Policy {
    std::string letter;
    std::size_t first_pos { 1 };
    std::size_t second_pos { 1 };
};

Policy parse_policy(std::string const& policy)
{
    std::regex const re { "^(\\d+)-(\\d+) ([a-z]+)" };
    std::smatch match;
    std::regex_search(policy, match, re);

    // index 0 is the full match, index 1 is the first capture group
    std::size_t const first_pos = std::stoul(match[1].str());
    std::size_t const second_pos = std::stoul(match[2].str());
    std::string const expected_letter = match[3].str();
    return Policy { expected_letter, first_pos, second_pos };
}

bool is_password_correct(std::string const& policy, std::string const& password)
{
    auto const parsed_policy = parse_policy(policy);

    std::size_t const first_pos_idx = parsed_policy.first_pos - 1;
    std::size_t const second_pos_idx = parsed_policy.second_pos - 1;
    bool first_letter_found = false;
    bool second_letter_found = false;

    if (first_pos_idx <= password.length()) {
        first_letter_found = std::string { password[first_pos_idx] } == parsed_policy.letter;
    }

    if (second_pos_idx <= password.length()) {
        second_letter_found = std::string { password[second_pos_idx] } == parsed_policy.letter;
    }

    if (first_pos_idx == second_pos_idx) {
        return (first_letter_found || second_letter_found);

    } else {
        return (first_letter_found ^ second_letter_found);
    }
}
