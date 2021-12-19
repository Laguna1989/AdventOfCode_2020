#ifndef CODE_KATA_PASSPORT_HPP
#define CODE_KATA_PASSPORT_HPP

#include <optional>
#include <string>

struct Passport {
    std::optional<int> byr;
    std::optional<int> iyr;
    std::optional<int> eyr;
    std::optional<std::string> hgt;
    std::optional<std::string> hcl;
    std::optional<std::string> ecl;
    std::optional<std::string> pid;
    std::optional<int> cid;
};

bool operator==(Passport const& a, Passport const& b);

#endif // CODE_KATA_PASSPORT_HPP
