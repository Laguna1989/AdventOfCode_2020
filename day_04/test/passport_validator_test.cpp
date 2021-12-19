#include "passport_validator.hpp"
#include "gtest/gtest.h"

TEST(PassportValidatorTest, EmptyPassportIsInvalid)
{
    Passport p;
    ASSERT_FALSE(check_is_valid_passport(p));
}

Passport get_passport_with_all_fields()
{
    return Passport { { 1937 }, { 2017 }, { 2020 }, { "183cm" }, { "#fffffd" }, { "gry" },
        { "860033327" }, { 147 } };
}

TEST(PassportValidatorTest, PassportWithAllFieldsIsValid)
{
    auto p = get_passport_with_all_fields();
    ASSERT_TRUE(check_is_valid_passport(p));
}

TEST(PassportValidatorTest, PassportWithoutHeightIsInvalid)
{
    auto p = get_passport_with_all_fields();
    p.hgt = {};
    ASSERT_FALSE(check_is_valid_passport(p));
}

TEST(PassportValidatorTest, PassportWithoutCountryIdIsValid)
{
    auto p = get_passport_with_all_fields();
    p.cid = {};
    ASSERT_TRUE(check_is_valid_passport(p));
}

TEST(PassportValidatorTest, PassportWithoutBirthIsInvalid)
{
    auto p = get_passport_with_all_fields();
    p.byr = {};
    ASSERT_FALSE(check_is_valid_passport(p));
}

TEST(PassportValidatorTest, PassportWithoutIssueIsInvalid)
{
    auto p = get_passport_with_all_fields();
    p.iyr = {};
    ASSERT_FALSE(check_is_valid_passport(p));
}

TEST(PassportValidatorTest, PassportWithoutExpirationIsInvalid)
{
    auto p = get_passport_with_all_fields();
    p.eyr = {};
    ASSERT_FALSE(check_is_valid_passport(p));
}

TEST(PassportValidatorTest, PassportWithoutHairIsInvalid)
{
    auto p = get_passport_with_all_fields();
    p.hcl = {};
    ASSERT_FALSE(check_is_valid_passport(p));
}

TEST(PassportValidatorTest, PassportWithoutEyeIsInvalid)
{
    auto p = get_passport_with_all_fields();
    p.ecl = {};
    ASSERT_FALSE(check_is_valid_passport(p));
}

TEST(PassportValidatorTest, PassportWithoutPassportIDIsInvalid)
{
    auto p = get_passport_with_all_fields();
    p.pid = {};
    ASSERT_FALSE(check_is_valid_passport(p));
}

class PassportValidatorBirthYearTestFixture
    : public ::testing::TestWithParam<std::pair<std::optional<int>, bool>> {
};

TEST_P(PassportValidatorBirthYearTestFixture, BirthYear)
{
    auto const byr = GetParam().first;
    auto const expected = GetParam().second;

    ASSERT_EQ(validate_birth_year(byr), expected);
}

INSTANTIATE_TEST_SUITE_P(PassportValidatorBirthYearTest, PassportValidatorBirthYearTestFixture,
    ::testing::Values(std::make_pair(std::optional<int> {}, false),
        std::make_pair(std::optional<int> { 2000 }, true),
        std::make_pair(std::optional<int> { 1919 }, false),
        std::make_pair(std::optional<int> { 1920 }, true),
        std::make_pair(std::optional<int> { 2003 }, false),
        std::make_pair(std::optional<int> { 2002 }, true)));

class PassportValidatorIssueYearTestFixture
    : public ::testing::TestWithParam<std::pair<std::optional<int>, bool>> {
};

TEST_P(PassportValidatorIssueYearTestFixture, IssueYear)
{
    auto const iyr = GetParam().first;
    auto const expected = GetParam().second;

    ASSERT_EQ(validate_issue_year(iyr), expected);
}

INSTANTIATE_TEST_SUITE_P(PassportValidatorIssueYearTest, PassportValidatorIssueYearTestFixture,
    ::testing::Values(std::make_pair(std::optional<int> {}, false),
        std::make_pair(std::optional<int> { 2015 }, true),
        std::make_pair(std::optional<int> { 2009 }, false),
        std::make_pair(std::optional<int> { 2010 }, true),
        std::make_pair(std::optional<int> { 2021 }, false),
        std::make_pair(std::optional<int> { 2020 }, true)));

class PassportValidatorExpirationYearTestFixture
    : public ::testing::TestWithParam<std::pair<std::optional<int>, bool>> {
};

TEST_P(PassportValidatorExpirationYearTestFixture, ExpirationYear)
{
    auto const iyr = GetParam().first;
    auto const expected = GetParam().second;

    ASSERT_EQ(validate_expiration_year(iyr), expected);
}

INSTANTIATE_TEST_SUITE_P(PassportValidatorExpirationYearTest,
    PassportValidatorExpirationYearTestFixture,
    ::testing::Values(std::make_pair(std::optional<int> {}, false),
        std::make_pair(std::optional<int> { 2025 }, true),
        std::make_pair(std::optional<int> { 2019 }, false),
        std::make_pair(std::optional<int> { 1972 }, false),
        std::make_pair(std::optional<int> { 2020 }, true),
        std::make_pair(std::optional<int> { 2031 }, false),
        std::make_pair(std::optional<int> { 2030 }, true)));

class PassportValidatorHeightTestFixture
    : public ::testing::TestWithParam<std::pair<std::optional<std::string>, bool>> {
};

TEST_P(PassportValidatorHeightTestFixture, Height)
{
    auto hgt = GetParam().first;
    auto expected = GetParam().second;
    ASSERT_EQ(validate_height(hgt), expected);
}

INSTANTIATE_TEST_SUITE_P(PassportValidatorHeightTest, PassportValidatorHeightTestFixture,
    ::testing::Values(std::make_pair(std::optional<std::string> {}, false),
        std::make_pair(std::optional<std::string> { "169cm" }, true),
        std::make_pair(std::optional<std::string> { "59in" }, true),
        std::make_pair(std::optional<std::string> { "abcd1234" }, false),
        std::make_pair(std::optional<std::string> { "abcd" }, false),
        std::make_pair(std::optional<std::string> { "1234" }, false)));

class PassportValidatorHairTestFixture
    : public ::testing::TestWithParam<std::pair<std::optional<std::string>, bool>> {
};

TEST_P(PassportValidatorHairTestFixture, Hair)
{
    auto hcl = GetParam().first;
    auto expected = GetParam().second;
    ASSERT_EQ(validate_hair(hcl), expected);
}

INSTANTIATE_TEST_SUITE_P(PassportValidatorHairTest, PassportValidatorHairTestFixture,
    ::testing::Values(std::make_pair(std::optional<std::string> {}, false),
        std::make_pair(std::optional<std::string> { "#fffffd" }, true),
        std::make_pair(std::optional<std::string> { "#cfa07d" }, true),
        std::make_pair(std::optional<std::string> { "#ae17e1" }, true),
        std::make_pair(std::optional<std::string> { "#xxxxxx" }, false),
        std::make_pair(std::optional<std::string> { "#1" }, false)));

class PassportValidatorEyeTestFixture
    : public ::testing::TestWithParam<std::pair<std::optional<std::string>, bool>> {
};

TEST_P(PassportValidatorEyeTestFixture, Eye)
{
    auto ecl = GetParam().first;
    auto expected = GetParam().second;
    ASSERT_EQ(validate_eye(ecl), expected);
}

INSTANTIATE_TEST_SUITE_P(PassportValidatorEyeTest, PassportValidatorEyeTestFixture,
    ::testing::Values(std::make_pair(std::optional<std::string> {}, false),
        std::make_pair(std::optional<std::string> { "amb" }, true),
        std::make_pair(std::optional<std::string> { "blu" }, true),
        std::make_pair(std::optional<std::string> { "brn" }, true),
        std::make_pair(std::optional<std::string> { "gry" }, true),
        std::make_pair(std::optional<std::string> { "grn" }, true),
        std::make_pair(std::optional<std::string> { "hzl" }, true),
        std::make_pair(std::optional<std::string> { "oth" }, true),
        std::make_pair(std::optional<std::string> { "nix" }, false)));

class PassportValidatorPidTestFixture
    : public ::testing::TestWithParam<std::pair<std::optional<std::string>, bool>> {
};

TEST_P(PassportValidatorPidTestFixture, Eye)
{
    auto pid = GetParam().first;
    auto expected = GetParam().second;
    ASSERT_EQ(validate_pid(pid), expected);
}

INSTANTIATE_TEST_SUITE_P(PassportValidatorPidTest, PassportValidatorPidTestFixture,
    ::testing::Values(std::make_pair(std::optional<std::string> {}, false),
        std::make_pair(std::optional<std::string> { "123456789" }, true),
        std::make_pair(std::optional<std::string> { "860033327" }, true),
        std::make_pair(std::optional<std::string> { "123" }, false)));
