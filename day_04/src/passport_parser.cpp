#include "passport_parser.hpp"
#include "splitstring.hpp"
#include <algorithm>
#include <regex>
#include <stdexcept>
#include <string>

namespace {
void parse_single_argument(Passport& p, std::string const& pair)
{
    SplitString ss { pair };
    auto split = ss.split(':');
    if (split.size() != 2) {
        throw std::invalid_argument { "invalid argument to parse: " + pair };
    }
    if (split[0] == "ecl") {
        p.ecl = split[1];
    } else if (split[0] == "pid") {
        p.pid = split[1];
    } else if (split[0] == "eyr") {
        p.eyr = std::stoi(split[1]);
    } else if (split[0] == "hcl") {
        p.hcl = split[1];
    } else if (split[0] == "byr") {
        p.byr = std::stoi(split[1]);
    } else if (split[0] == "iyr") {
        p.iyr = std::stoi(split[1]);
    } else if (split[0] == "cid") {
        p.cid = std::stoi(split[1]);
    } else if (split[0] == "hgt") {
        p.hgt = split[1];
    }
}

} // namespace

Passport parse_single_passport(std::string const& string)
{
    if (string.empty()) {
        return Passport {};
    }

    Passport p;

    std::string copy = std::regex_replace(string, std::regex("\n"), " ");

    SplitString splitString { copy };

    auto splits = splitString.split(' ');
    if (splits.size() == 1) { // size of 1 means no split found. So use the full string as an input
        parse_single_argument(p, string);
    } else {
        for (auto const s : splits) {
            parse_single_argument(p, s);
        }
    }
    return p;
}
std::vector<Passport> parse_multiple_passports(std::string const& string)
{
    std::vector<Passport> passports;
    if (string.empty()) {
        return passports;
    }

    std::string copy = std::regex_replace(string, std::regex("\n\n"), "=");
    SplitString splitString { copy };
    auto splits = splitString.split('=');
    for (auto s : splits) {
        passports.push_back(parse_single_passport(s));
    }
    return passports;
}
