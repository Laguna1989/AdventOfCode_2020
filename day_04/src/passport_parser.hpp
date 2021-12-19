#ifndef CODE_KATA_PASSPORT_PARSER_HPP
#define CODE_KATA_PASSPORT_PARSER_HPP

#include "passport.hpp"
#include <vector>

Passport parse_single_passport(std::string const& string);

std::vector<Passport> parse_multiple_passports(std::string const& string);

#endif // CODE_KATA_PASSPORT_PARSER_HPP
