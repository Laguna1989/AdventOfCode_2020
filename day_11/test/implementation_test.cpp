#include "implementation.hpp"
#include <gtest/gtest.h>

struct Position {
    int x, y;
};



class Ferry {
 public:
     Ferry(std::string const& input);

     bool is_seat(Position const& p)
     {
         return false;
     }
};

Ferry::Ferry(const std::string& input)
{

}


TEST(ParseInput, SimpleInputIsParsedCorrectly) {
    auto input = "L";
    Ferry f(input);

    ASSERT_TRUE(f.is_seat(Position{0, 0}));
}

