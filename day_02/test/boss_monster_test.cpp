#include "is_password_correct.hpp"
#include "split_input.hpp"
#include <fstream>
#include <gtest/gtest.h>

using namespace ::testing;

TEST(BossMonsterTest, TestSmallBatch)
{
    std::string const input = R"(1-3 a: abcde
1-3 b: cdefg
2-9 c: ccccccccc)";

    std::stringstream ss(input);
    std::string line;
    int count { 0 };
    while (std::getline(ss, line, '\n')) {
        auto [policy, password] = split_input(line);
        if (is_password_correct(policy, password)) {
            count++;
        }
    }

    ASSERT_EQ(count, 1);
}

TEST(BossMonsterTest, TestBigBatch)
{
    std::ifstream file { "full_puzzle_input.txt" };

    std::string line;
    int count { 0 };
    while (std::getline(file, line, '\n')) {
        auto [policy, password] = split_input(line);
        if (is_password_correct(policy, password)) {
            count++;
        }
    }

    ASSERT_EQ(count, 694);
}
