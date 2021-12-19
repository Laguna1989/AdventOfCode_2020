#include "data.hpp"
#include <iostream>
#include <set>


// Idea:
// set<int> which contains the elements in an ordered way
// three iterators on data.
//      * One starts from begin (left)
//      * One starts from begin+1 (center)
//      * One starts from rbegin (right)
//
// Steps in the algorithm:
//      * move (right)  through the data in reversed order
//          * until (right) == (center)
//          * if sum < 2020 break, because we will only encounter smaller values for the (right) iterator.
//      * reset (right) to rbegin and move center 1 to the right
//      * move (center) until it reaches (right)
//      * move (left) one to the right and set (center) to left +1
//      * for each combination, check if the sum of values is 2020, and if so, print product
//
// Possible optimization:
//      * instead of moving (right) by steps of 1, a bisection algorithm could be used to speed up finding the right entry

void sum_of_three(std::set<int> const &data) {
    auto it_left = data.cbegin();
    while (true) {
        auto it_center = it_left;

        while (true) {
            auto it_right = data.crbegin();
            while (true) {
                auto num_left = *it_left;
                auto num_center = *it_center;
                auto num_right = *it_right;

                int sum = num_left + num_right + num_center;
                if (sum < 2020) { break; }
                if (sum == 2020) {
                    std::cout << "\taccept: " << sum << " product: " << num_left * num_right * num_center << std::endl;
                    return;
                }
                if (num_right == num_center) {
                    break;
                }
                ++it_right;
            }
            it_center++;
            if (it_center == (--data.cend())) {
                break;
            }
        }
        ++it_left;
        if (it_left == data.cend()) {
            std::cout << "no combination of entries found\n";
            break;
        }
    }
}

int main() {

    sum_of_three(test_set_full);

    return 0;
}
