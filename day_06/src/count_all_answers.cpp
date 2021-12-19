#include "count_all_answers.hpp"
#include "count_answers_in_group.hpp"
#include "split_input_into_groups.hpp"

int countQuestionsAnyoneAnsweredYes(std::string const& input)
{
    auto const groups = splitInputIntoGroups(input);

    int sum = 0;
    for (auto const& g : groups) {
        sum += countUniqueAnswersInGroup(g);
    }

    return sum;
}

int countQuestionsEveryoneAnsweredYes(std::string const& input)
{
    auto const groups = splitInputIntoGroups(input);

    int sum = 0;
    for (auto const& g : groups) {
        sum += countCommonAnswersInGroup(g);
    }

    return sum;
}
