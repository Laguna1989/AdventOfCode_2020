#include "passport.hpp"

bool operator==(Passport const& a, Passport const& b)
{
    return a.byr == b.byr && a.cid == b.cid && a.ecl == b.ecl && a.eyr == b.eyr && a.hcl == b.hcl
        && a.hgt == b.hgt && a.iyr == b.iyr && a.pid == b.pid;
}
