#include "passport_validator.hpp"
#include <regex>

bool check_is_valid_passport(Passport const& p)
{
    return validate_birth_year(p.byr) && validate_issue_year(p.iyr)
        && validate_expiration_year(p.eyr) && validate_height(p.hgt) && validate_hair(p.hcl)
        && validate_eye(p.ecl) && validate_pid(p.pid);
}

bool validate_year(std::optional<int> opt_value, int min_value, int max_value)
{
    if (!opt_value.has_value()) {
        return false;
    }
    auto const v = opt_value.value();
    return (v >= min_value && v <= max_value);
}

bool validate_birth_year(std::optional<int> const& byr) { return validate_year(byr, 1920, 2002); }
bool validate_issue_year(std::optional<int> const& byr) { return validate_year(byr, 2010, 2020); }
bool validate_expiration_year(std::optional<int> const& eyr)
{
    return validate_year(eyr, 2020, 2030);
}
bool validate_height(std::optional<std::string> opt_value)
{
    if (!opt_value.has_value()) {
        return false;
    }
    auto const v = opt_value.value();
    std::regex const regex_matcher_cm("1[5-8][0-9]cm|19[0-3]cm");
    std::regex const regex_matcher_in("59in|[6-7][0-9]in|7[0-7]in");
    return std::regex_match(v, regex_matcher_cm) || std::regex_match(v, regex_matcher_in);
}

bool validate_hair(std::optional<std::string> opt_value)
{
    if (!opt_value.has_value()) {
        return false;
    }
    auto const v = opt_value.value();
    std::regex const regex_matcher("#[0-9a-f]{6}");
    return std::regex_match(v, regex_matcher);
}

bool validate_eye(std::optional<std::string> opt_value)
{
    if (!opt_value.has_value()) {
        return false;
    }
    auto const v = opt_value.value();
    std::regex const regex_matcher("amb|blu|brn|gry|grn|hzl|oth");
    return std::regex_match(v, regex_matcher);
}

bool validate_pid(std::optional<std::string> opt_value)
{
    if (!opt_value.has_value()) {
        return false;
    }
    auto const v = opt_value.value();
    std::regex const regex_matcher("[0-9]{9}");
    return std::regex_match(v, regex_matcher);
}
