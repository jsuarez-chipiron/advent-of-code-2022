#include <iostream>
#include <functional>
#include <timer.h>
#include "lib.h"

template<std::size_t N>
bool is_valid_key(std::string& s)
{
    std::sort(s.begin(), s.end());
    char c = s[0];
    for (size_t i=1; i<=(N-1); ++i)
    {
        if ( c == s.at(i) )
        {
            return false;
        }
        c = s.at(i);
    }
    return true;
}

template<std::size_t N>
size_t perform(const std::string& input_filename)
{
    auto input = read_input(input_filename).at(0);
    size_t input_length = input.length();

    for (size_t i=0; i<input_length-(N-1); ++i)
    {
        std::string s = input.substr(i,N);
        if ( is_valid_key<N>(s) )
        {
            return i+N;
        }
    }
    return 0;
}

int main(int /*argc*/, char ** /*argv*/)
{
    timer t;
    auto result = perform<4>("../inputs/day6.txt");
    std::cout << "day 6 part 1 result: " << result << " in " << t.elapsed_micro() << "us\n";

    t.reset();
    result = perform<14>("../inputs/day6.txt");
    std::cout << "day 6 part 2 result: " << result << " in " << t.elapsed_micro() << "us\n";
    return 0;
}
