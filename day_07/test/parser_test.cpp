#include "parser.hpp"
#include <gtest/gtest.h>

using namespace ::testing;

class ParserContainerTestFixture
    : public ::testing::TestWithParam<std::tuple<std::string, std::string>> {
};

TEST_P(ParserContainerTestFixture, ContainerIsCorrect)
{
    auto const input = std::get<0>(GetParam());
    auto const container = parseOneLine(input);
    auto const expected = std::get<1>(GetParam());

    ASSERT_EQ(container.identifier, expected);
}

INSTANTIATE_TEST_SUITE_P(ParserContainerTest, ParserContainerTestFixture,
    ::testing::Values(std::make_tuple("dotted black bags contain no other bags.", "dotted black"),
        std::make_tuple("dotted brown bags contain no other bags.", "dotted brown"),
        std::make_tuple(
            "vibrant plum bags contain 5 faded blue bags, 6 dotted black bags.", "vibrant plum")));

class ParserContaineeTestFixture
    : public ::testing::TestWithParam<std::tuple<std::string, std::vector<Token>>> {
};

TEST_P(ParserContaineeTestFixture, ContainsCorrectSize)
{
    auto const input = std::get<0>(GetParam());
    auto const expected = std::get<1>(GetParam());
    auto const container = parseOneLine(input);

    ASSERT_EQ(container.containedTokens.size(), expected.size());
}

TEST_P(ParserContaineeTestFixture, ContainsCorrectCount)
{
    auto const input = std::get<0>(GetParam());
    auto const expected = std::get<1>(GetParam());
    auto const container = parseOneLine(input);

    for (auto i = 0U; i != container.containedTokens.size(); ++i) {
        ASSERT_EQ(container.containedTokens.at(i).count, expected.at(i).count);
    }
}

TEST_P(ParserContaineeTestFixture, ContainsCorrectIdentifer)
{
    auto const input = std::get<0>(GetParam());
    auto const expected = std::get<1>(GetParam());
    auto const container = parseOneLine(input);
    for (auto i = 0U; i != container.containedTokens.size(); ++i) {
        ASSERT_EQ(container.containedTokens.at(i).identifier, expected.at(i).identifier);
    }
}

INSTANTIATE_TEST_SUITE_P(ParserContaineeTest, ParserContaineeTestFixture,
    ::testing::Values(std::make_tuple("bright white bags contain 1 shiny gold bag.",
                          std::vector<Token> { Token { "shiny gold", 1 } }),
        std::make_tuple("vibrant plum bags contain 5 faded blue bags.",
            std::vector<Token> { Token { "faded blue", 5 } }),
        std::make_tuple("dotted black bags contain no other bags.", std::vector<Token> {}),
        std::make_tuple("vibrant orange bags contain 3 plaid tan bags, 4 dotted blue bags, 3 "
                        "bright gold bags, 3 bright white bags.",
            std::vector<Token> { { "plaid tan", 3 }, { "dotted blue", 4 }, { "bright gold", 3 },
                { "bright white", 3 } })));

TEST(ParserMultipleContaineeTestFixture, ParseMultipleContaineesSize)
{
    auto const input = "vibrant plum bags contain 5 faded blue bags, 6 dotted black bags.";
    auto container = parseOneLine(input);
    ASSERT_EQ(container.containedTokens.size(), 2U);
}

TEST(ParserMultipleLinesTest, ParseMultipleLines)
{
    std::string inputString = R"(light red bags contain 1 bright white bag, 2 muted yellow bags.
dark orange bags contain 3 bright white bags, 4 muted yellow bags.
bright white bags contain 1 shiny gold bag.
)";
    auto containers = parseMultipleLines(inputString);
    Container containerA { "light red",
        { Token { "bright white", 1 }, Token { "muted yellow", 2 } } };
    Container containerB { "dark orange",
        { Token { "bright white", 3 }, Token { "muted yellow", 4 } } };
    Container containerC { "bright white", { Token { "shiny gold", 1 } } };

    std::vector<Container> expectedContainers { containerA, containerB, containerC };

    ASSERT_EQ(containers.at(0).identifier, expectedContainers.at(0).identifier);
    ASSERT_EQ(containers.at(1).identifier, expectedContainers.at(1).identifier);
    ASSERT_EQ(containers.at(2).identifier, expectedContainers.at(2).identifier);
}
