#include "parser.hpp"
#include <gtest/gtest.h>

TEST(ListTest, EmptyListReturnsEmptyList)
{
    auto validContainers = listValidContainers({}, "abc");
    EXPECT_TRUE(validContainers.empty());
}

TEST(ListTest, ListWithoutRootBagReturnsEmptyList)
{
    Container const container = Container { "", std::vector<Token> { Token { "", 1 } } };
    std::vector<Container> const containers { container };
    auto const validContainers = listValidContainers(containers, "abc");
    EXPECT_TRUE(validContainers.empty());
}

TEST(ListTest, ListWithRootBagReturnsOneEntry)
{
    Container const container = Container { "blue", std::vector<Token> { Token { "abc", 1 } } };
    std::vector<Container> const containers { container };
    auto const validContainers = listValidContainers(containers, "abc");
    EXPECT_FALSE(validContainers.empty());
}

TEST(ListTest, ListWithTwoEntriesOneRootBag)
{
    Container const containerA = Container { "blue", std::vector<Token> { Token { "abc", 1 } } };
    Container const containerB = Container { "yellow", std::vector<Token> { Token { "def", 1 } } };
    std::vector<Container> const containers { containerA, containerB };
    auto const validContainers = listValidContainers(containers, "abc");

    EXPECT_EQ(validContainers.count("blue"), 1);
}

TEST(ListTest, ListWithTwoEntries)
{
    Container const containerA = Container { "blue", std::vector<Token> { Token { "abc", 1 } } };
    Container const containerB = Container { "yellow", std::vector<Token> { Token { "abc", 1 } } };
    std::vector<Container> const containers { containerA, containerB };
    auto const validContainers = listValidContainers(containers, "abc");

    EXPECT_EQ(validContainers.count("blue"), 1);
    EXPECT_EQ(validContainers.count("yellow"), 1);
}

TEST(ListTest, ListWithOneEntriesTwoTokens)
{
    Container const containerA
        = Container { "blue", std::vector<Token> { Token { "abc", 1 }, Token { "yellow", 1 } } };
    std::vector<Container> const containers { containerA };
    auto const validContainers = listValidContainers(containers, "abc");

    EXPECT_EQ(validContainers.count("blue"), 1);
}

TEST(ListTest, ListWithSingleIndirection)
{
    Container const containerA = Container { "blue", std::vector<Token> { Token { "orange", 1 } } };
    Container const containerB = Container { "orange", std::vector<Token> { Token { "abc", 1 } } };
    std::vector<Container> const containers { containerA, containerB };
    auto const validContainers = listValidContainers(containers, "abc");

    EXPECT_EQ(validContainers.count("orange"), 1);
    EXPECT_EQ(validContainers.count("blue"), 1);
}

TEST(ListTest, ListWithDualIndirection)
{
    Container const containerA = Container { "blue", std::vector<Token> { Token { "orange", 1 } } };
    Container const containerB
        = Container { "orange", std::vector<Token> { Token { "yellow", 1 } } };
    Container const containerC = Container { "yellow", std::vector<Token> { Token { "abc", 1 } } };
    std::vector<Container> const containers { containerA, containerB, containerC };
    auto const validContainers = listValidContainers(containers, "abc");

    EXPECT_EQ(validContainers.count("yellow"), 1);
    EXPECT_EQ(validContainers.count("orange"), 1);
    EXPECT_EQ(validContainers.count("blue"), 1);
}

TEST(ListTest, ListWithTripleIndirection)
{
    Container const containerA = Container { "blue", std::vector<Token> { Token { "orange", 1 } } };
    Container const containerB
        = Container { "orange", std::vector<Token> { Token { "yellow", 1 } } };
    Container const containerC
        = Container { "yellow", std::vector<Token> { Token { "green", 1 } } };
    Container const containerD = Container { "green", std::vector<Token> { Token { "abc", 1 } } };
    std::vector<Container> const containers { containerA, containerB, containerC, containerD };
    auto const validContainers = listValidContainers(containers, "abc");

    EXPECT_EQ(validContainers.count("green"), 1);
    EXPECT_EQ(validContainers.count("yellow"), 1);
    EXPECT_EQ(validContainers.count("orange"), 1);
    EXPECT_EQ(validContainers.count("blue"), 1);
}

TEST(ListTest, ListWithTripleIndirectionReversed)
{
    Container const containerA = Container { "blue", std::vector<Token> { Token { "orange", 1 } } };
    Container const containerB
        = Container { "orange", std::vector<Token> { Token { "yellow", 1 } } };
    Container const containerC
        = Container { "yellow", std::vector<Token> { Token { "green", 1 } } };
    Container const containerD = Container { "green", std::vector<Token> { Token { "abc", 1 } } };
    std::vector<Container> const containers { containerD, containerC, containerB, containerA };
    auto const validContainers = listValidContainers(containers, "abc");

    EXPECT_EQ(validContainers.count("green"), 1);
    EXPECT_EQ(validContainers.count("yellow"), 1);
    EXPECT_EQ(validContainers.count("orange"), 1);
    EXPECT_EQ(validContainers.count("blue"), 1);
}

TEST(ListTest, ListWithTwoEntriesAndSingleIndirection)
{
    Container const containerA = Container { "blue", std::vector<Token> { Token { "abc", 1 } } };
    Container const containerB
        = Container { "yellow", std::vector<Token> { Token { "green", 1 } } };
    Container const containerC = Container { "green", std::vector<Token> { Token { "abc", 1 } } };
    std::vector<Container> const containers { containerA, containerB, containerC };
    auto const validContainers = listValidContainers(containers, "abc");

    EXPECT_EQ(validContainers.count("blue"), 1);
    EXPECT_EQ(validContainers.count("green"), 1);
    EXPECT_EQ(validContainers.count("yellow"), 1);
}

TEST(ListTest, ListWithComplicatedIndirection)
{
    Container const containerA
        = Container { "red", std::vector<Token> { Token { "abc", 1 }, Token { "green", 1 } } };
    Container const containerB = Container { "green", std::vector<Token> { Token { "abc", 1 } } };
    std::vector<Container> const containers { containerA, containerB };
    auto const validContainers = listValidContainers(containers, "abc");

    EXPECT_EQ(validContainers.count("red"), 1);
    EXPECT_EQ(validContainers.count("green"), 1);
    ASSERT_EQ(validContainers.size(), 2);
}

TEST(NeededContainersFor, EmptyListReturnsZero)
{
    std::vector<Container> containers {};
    auto const needed = neededContainersFor(containers, "shiny gold");
    ASSERT_EQ(needed, 0);
}

class NeededContainerSingleTestFixture
    : public ::testing::TestWithParam<std::tuple<Container, std::size_t>> {
};

TEST_P(NeededContainerSingleTestFixture, NeededContainerSingleTest)
{
    Container const container = std::get<0>(GetParam());
    auto expectedSize = std::get<1>(GetParam());

    std::vector<Container> const containers { container };
    auto const needed = neededContainersFor(containers, "shiny gold");
    ASSERT_EQ(needed, expectedSize);
}

INSTANTIATE_TEST_SUITE_P(NeededContainerSingleTest, NeededContainerSingleTestFixture,
    ::testing::Values(
        std::make_tuple(Container { "blue", std::vector<Token> { Token { "abc", 1 } } }, 0),
        std::make_tuple(Container { "shiny gold", std::vector<Token> { Token { "abc", 1 } } }, 1),
        std::make_tuple(Container { "shiny gold", std::vector<Token> { Token { "abc", 2 } } }, 2),
        std::make_tuple(Container { "shiny gold",
                            std::vector<Token> { Token { "abc", 1 }, Token { "def", 1 } } },
            2),
        std::make_tuple(Container { "shiny gold",
                            std::vector<Token> { Token { "abc", 2 }, Token { "def", 2 } } },
            4)));

TEST(NeededContainersFor, ListWithTwoContainerOneTokenCountOneReturnsThree)
{
    Container const containerA
        = Container { "shiny gold", std::vector<Token> { Token { "blue", 1 } } };
    Container const containerB = Container { "blue", std::vector<Token> { Token { "abc", 1 } } };
    std::vector<Container> const containers { containerA, containerB };
    auto const needed = neededContainersFor(containers, "shiny gold");
    ASSERT_EQ(needed, 2);
}

TEST(NeededContainersFor, ListWithTwoContainersOneTokenCountTwoReturnsFour)
{
    Container const containerA
        = Container { "shiny gold", std::vector<Token> { Token { "blue", 1 } } };
    Container const containerB = Container { "blue", std::vector<Token> { Token { "abc", 2 } } };
    std::vector<Container> const containers { containerA, containerB };
    auto const needed = neededContainersFor(containers, "shiny gold");
    ASSERT_EQ(needed, 3);
}

TEST(NeededContainersFor, ListWithTwoContainersOneTokenCountTwoReturnsSeven)
{
    Container const containerA
        = Container { "shiny gold", std::vector<Token> { Token { "blue", 3 } } };
    Container const containerB = Container { "blue", std::vector<Token> { Token { "abc", 1 } } };
    std::vector<Container> const containers { containerA, containerB };
    auto const needed = neededContainersFor(containers, "shiny gold");
    ASSERT_EQ(needed, 6);
}

TEST(NeededContainersFor, ListWithThreeContainersOneTokenEachReturnsSeven)
{
    Container const containerA
        = Container { "shiny gold", std::vector<Token> { Token { "blue", 2 } } };
    Container const containerB = Container { "blue", std::vector<Token> { Token { "green", 1 } } };
    Container const containerC = Container { "green", std::vector<Token> { Token { "abc", 1 } } };
    std::vector<Container> const containers { containerA, containerB, containerC };
    auto const needed = neededContainersFor(containers, "shiny gold");
    ASSERT_EQ(needed, 6);
}
