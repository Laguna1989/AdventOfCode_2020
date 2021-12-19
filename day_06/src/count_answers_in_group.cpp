#include "count_answers_in_group.hpp"
#include "split_input_into_groups.hpp"
#include <algorithm>
#include <regex>

void removeNewlines(std::string& input_copy)
{
    input_copy.erase(std::remove(input_copy.begin(), input_copy.end(), '\n'), input_copy.end());
}

template <typename T>
void makeUnique(T& container)
{
    std::sort(container.begin(), container.end());
    container.erase(std::unique(container.begin(), container.end()), container.end());
}

int countUniqueAnswersInGroup(std::string const& group_input)
{
    std::string input_copy = group_input;
    removeNewlines(input_copy);
    makeUnique(input_copy);

    return static_cast<int>(input_copy.length());
}

std::vector<std::string> splitGroupInputIntoPersons(std::string const& group_input)
{
    if (group_input.empty()) {
        return {};
    }

    std::vector<std::string> result;
    std::regex const regex { "\n" };
    std::sregex_token_iterator iter(group_input.begin(), group_input.end(), regex, -1);

    for (std::sregex_token_iterator end; iter != end; ++iter) {
        result.emplace_back(iter->str());
    }

    return result;
}

int countCommonAnswersInGroup(std::string const& group_input)
{
    auto persons_in_group = splitGroupInputIntoPersons(group_input);

    std::vector<char> all_answers;

    for (auto p : persons_in_group) {
        for (auto c : p) {
            all_answers.push_back(c);
        }
    }

    auto const size = persons_in_group.size();
    auto const checkIfCommonElement = [size, &all_answers](auto const c) {
        return std::count(all_answers.begin(), all_answers.end(), c) != size;
    };

    all_answers.erase(std::remove_if(all_answers.begin(), all_answers.end(), checkIfCommonElement),
        all_answers.end());

    makeUnique(all_answers);

    return all_answers.size();
}
