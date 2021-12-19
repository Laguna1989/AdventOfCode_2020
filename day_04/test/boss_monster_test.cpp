#include "passport_parser.hpp"
#include "passport_validator.hpp"
#include "test_data.hpp"
#include "gtest/gtest.h"
#include <fstream>

TEST(BossMonsterTest, CorrectAmountOfPassportsIsValidForSmallDataSet)
{
    auto const passports = parse_multiple_passports(small_data_set);

    int count = 0;
    for (auto const& p : passports) {
        if (check_is_valid_passport(p)) {
            count++;
        }
    }

    ASSERT_EQ(count, 2);
}

TEST(BossMonsterTest, CorrectAmountOfPassportsIsValidForSmallInvalidDataSet)
{
    auto const passports = parse_multiple_passports(small_invalid_data_set);

    int count = 0;
    for (auto const& p : passports) {
        if (check_is_valid_passport(p)) {
            count++;
        }
    }

    ASSERT_EQ(count, 0);
}

TEST(BossMonsterTest, CorrectAmountOfPassportsIsValidForSmallValidDataSet)
{
    auto const passports = parse_multiple_passports(small_valid_data_set);

    int count = 0;
    for (auto const& p : passports) {
        if (check_is_valid_passport(p)) {
            count++;
        }
    }

    ASSERT_EQ(count, 4);
}

TEST(BossMonsterTest, CorrectAmountOfPassportsIsValidForLargeDataSet)
{
    std::ifstream file { "large_test_data.txt" };
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string large_data_set = buffer.str();
    auto const passports = parse_multiple_passports(large_data_set);

    int count = 0;
    for (auto const& p : passports) {
        if (check_is_valid_passport(p)) {
            count++;
        }
    }

    ASSERT_EQ(count, 188);
}
