#include "passport.hpp"
#include "gtest/gtest.h"

using namespace ::testing;

TEST(PassportInitialTest, BirthYearIsNotSet)
{
    Passport p;
    ASSERT_FALSE(p.byr.has_value());
}

TEST(PassportInitialTest, IssueYearIsNotSet)
{
    Passport p;
    ASSERT_FALSE(p.iyr.has_value());
}

TEST(PassportInitialTest, ExpirationYearIsNotSet)
{
    Passport p;
    ASSERT_FALSE(p.eyr.has_value());
}

TEST(PassportInitialTest, HeightIsNotSet)
{
    Passport p;
    ASSERT_FALSE(p.hgt.has_value());
}

TEST(PassportInitialTest, HairColorIsNotSet)
{
    Passport p;
    ASSERT_FALSE(p.hcl.has_value());
}
TEST(PassportInitialTest, EyeColorIsNotSet)
{
    Passport p;
    ASSERT_FALSE(p.ecl.has_value());
}
TEST(PassportInitialTest, PassportIDIsNotSet)
{
    Passport p;
    ASSERT_FALSE(p.pid.has_value());
}
TEST(PassportInitialTest, CountryIDIsNotSet)
{
    Passport p;
    ASSERT_FALSE(p.cid.has_value());
}
