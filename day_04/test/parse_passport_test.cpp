#include "passport_parser.hpp"
#include "gtest/gtest.h"

TEST(ParsePassportTest, ParseEmptyStringResultsInEmptyPassport)
{
    Passport const expected;

    auto parsed = parse_single_passport("");
    ASSERT_EQ(parsed, expected);
}

class ParsePassportEntryTestFixture
    : public ::testing::TestWithParam<std::pair<std::string, Passport>> {
};

TEST_P(ParsePassportEntryTestFixture, ParseStringWithSingleEntryParsesEntry)
{
    std::string const input = GetParam().first;
    Passport expected = GetParam().second;

    auto parsed = parse_single_passport(input);
    ASSERT_EQ(parsed, expected);
}

INSTANTIATE_TEST_SUITE_P(ParsePassportSingleEntryTest, ParsePassportEntryTestFixture,
    ::testing::Values(std::make_pair("ecl:amb", Passport { {}, {}, {}, {}, {}, { "amb" }, {}, {} }),
        std::make_pair("ecl:gry", Passport { {}, {}, {}, {}, {}, { "gry" }, {}, {} }),
        std::make_pair("pid:860033327", Passport { {}, {}, {}, {}, {}, {}, { "860033327" }, {} }),
        std::make_pair("pid:760753108", Passport { {}, {}, {}, {}, {}, {}, { "760753108" }, {} }),
        std::make_pair("eyr:2025", Passport { {}, {}, { 2025 }, {}, {}, {}, {}, {} }),
        std::make_pair("eyr:2020", Passport { {}, {}, { 2020 }, {}, {}, {}, {}, {} }),
        std::make_pair("hcl:#fffffd", Passport { {}, {}, {}, {}, { "#fffffd" }, {}, {}, {} }),
        std::make_pair("hcl:#ae17e1", Passport { {}, {}, {}, {}, { "#ae17e1" }, {}, {}, {} }),
        std::make_pair("byr:1937", Passport { { 1937 }, {}, {}, {}, {}, {}, {}, {} }),
        std::make_pair("byr:1999", Passport { { 1999 }, {}, {}, {}, {}, {}, {}, {} }),
        std::make_pair("iyr:2017", Passport { {}, { 2017 }, {}, {}, {}, {}, {}, {} }),
        std::make_pair("iyr:2013", Passport { {}, { 2013 }, {}, {}, {}, {}, {}, {} }),
        std::make_pair("cid:147", Passport { {}, {}, {}, {}, {}, {}, {}, { 147 } }),
        std::make_pair("cid:350", Passport { {}, {}, {}, {}, {}, {}, {}, { 350 } }),
        std::make_pair("hgt:183cm", Passport { {}, {}, {}, { "183cm" }, {}, {}, {}, {} }),
        std::make_pair("hgt:59in", Passport { {}, {}, {}, { "59in" }, {}, {}, {}, {} })));

INSTANTIATE_TEST_SUITE_P(ParsePassportTwoEntriesTest, ParsePassportEntryTestFixture,
    ::testing::Values(std::make_pair(
        "ecl:gry pid:860033327", Passport { {}, {}, {}, {}, {}, { "gry" }, { "860033327" }, {} })));

auto single_line_full_entry_string
    = R"(ecl:gry pid:860033327 eyr:2020 hcl:#fffffd byr:1937 iyr:2017 cid:147 hgt:183cm)";
auto two_line_full_entry_string = R"(ecl:gry pid:860033327 eyr:2020 hcl:#fffffd
byr:1937 iyr:2017 cid:147 hgt:183cm)";

auto multi_line_full_entry_string = R"(hcl:#ae17e1 iyr:2013
eyr:2024
ecl:brn pid:760753108 byr:1931
hgt:179cm)";

auto expected_passport = Passport { { 1937 }, { 2017 }, { 2020 }, { "183cm" }, { "#fffffd" },
    { "gry" }, { "860033327" }, { 147 } };

auto expected_passport2 = Passport { { 1931 }, { 2013 }, { 2024 }, { "179cm" }, { "#ae17e1" },
    { "brn" }, { "760753108" }, {} };

INSTANTIATE_TEST_SUITE_P(ParsePassportFullEntriesTest, ParsePassportEntryTestFixture,
    ::testing::Values(std::make_pair(single_line_full_entry_string, expected_passport),
        std::make_pair(two_line_full_entry_string, expected_passport),
        std::make_pair(multi_line_full_entry_string, expected_passport2)));

TEST(ParseMultiplePassportsTestFixture, ParseEmptyString)
{
    std::string const input = R"()";
    std::vector<Passport> expected {};

    auto parsed = parse_multiple_passports(input);
    ASSERT_EQ(parsed, expected);
}

TEST(ParseMultiplePassportsTestFixture, ParseSinglePassport)
{
    std::string const input = single_line_full_entry_string;
    std::vector<Passport> expected {};
    expected.push_back(expected_passport);

    auto parsed = parse_multiple_passports(input);
    ASSERT_EQ(parsed, expected);
}

TEST(ParseMultiplePassportsTestFixture, ParseTwoPassports)
{
    std::string input = single_line_full_entry_string;
    input += "\n\n";
    input += multi_line_full_entry_string;
    std::vector<Passport> expected {};
    expected.push_back(expected_passport);
    expected.push_back(expected_passport2);

    auto parsed = parse_multiple_passports(input);
    ASSERT_EQ(parsed, expected);
}

TEST(ParseMultiplePassportsTestFixture, ParseCompleteSmallTestSet)
{
    std::string input =
        R"(ecl:gry pid:860033327 eyr:2020 hcl:#fffffd
byr:1937 iyr:2017 cid:147 hgt:183cm

iyr:2013 ecl:amb cid:350 eyr:2023 pid:028048884
hcl:#cfa07d byr:1929

hcl:#ae17e1 iyr:2013
eyr:2024
ecl:brn pid:760753108 byr:1931
hgt:179cm

hcl:#cfa07d eyr:2025 pid:166559648
iyr:2011 ecl:brn hgt:59in)";

    std::vector<Passport> expected {};
    expected.push_back(expected_passport);
    expected.push_back(Passport {
        { 1929 }, { 2013 }, { 2023 }, {}, { "#cfa07d" }, { "amb" }, { "028048884" }, { 350 } });
    expected.push_back(expected_passport2);
    expected.push_back(Passport {
        {}, { 2011 }, { 2025 }, { "59in" }, { "#cfa07d" }, { "brn" }, { "166559648" }, {} });

    auto parsed = parse_multiple_passports(input);
    ASSERT_EQ(parsed, expected);
}
