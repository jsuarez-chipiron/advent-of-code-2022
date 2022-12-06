#include <iostream>
#include <functional>
#include <timer.h>
#include "lib.h"

bool is_valid_key(std::string& s)
{
    std::sort(s.begin(), s.end());
    char c = s[0];
    for (size_t i=1; i<=3; ++i)
    {
        if ( c == s.at(i) )
        {
            return false;
        }
        c = s.at(i);
    }
    return true;
}

size_t perform(const std::string& input_filename)
{
    auto input = read_input(input_filename).at(0);
    size_t input_length = input.length();

    for (size_t i=0; i<input_length-3; ++i)
    {
        std::string s = input.substr(i,4);
        if ( is_valid_key(s) )
        {
            return i+4;
        }
    }
    return 0;
}

int main(int /*argc*/, char ** /*argv*/)
{
    timer t;
    auto result = perform("../inputs/day6.txt");
    std::cout << "day 6 part 1 result: " << result << " in " << t.elapsed_micro() << "us\n";

    return 0;
}
