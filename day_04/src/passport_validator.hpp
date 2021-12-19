#ifndef CODE_KATA_PASSPORT_VALIDATOR_HPP
#define CODE_KATA_PASSPORT_VALIDATOR_HPP

#include "passport.hpp"

bool check_is_valid_passport(Passport const& p);

bool validate_year(std::optional<int> opt_value, int min_value, int max_value);

bool validate_birth_year(std::optional<int> const& byr);
bool validate_issue_year(std::optional<int> const& byr);
bool validate_expiration_year(std::optional<int> const& eyr);

bool validate_height(std::optional<std::string> opt_value);
bool validate_hair(std::optional<std::string> opt_value);
bool validate_eye(std::optional<std::string> opt_value);
bool validate_pid(std::optional<std::string> opt_value);

#endif // CODE_KATA_PASSPORT_VALIDATOR_HPP
