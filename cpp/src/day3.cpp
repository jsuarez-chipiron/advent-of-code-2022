#include <iostream>
#include "lib.h" 
#include <algorithm>
#include <functional>
#include <numeric>
#include <timer.h>
#include <vector>
#include <utility>
#include <unordered_set>

uint32_t get_priority(uint32_t n)
{
    if ( n >= 97 )
    {
        return n-96;
    }
    return n-38;
}

uint32_t perform(const std::string& input_filename)
{
    auto lines = read_input(input_filename);

    uint32_t result = 0;

    std::for_each(lines.begin(), lines.end(), [&result](const std::string& s) {
        std::unordered_set<char> items;
        size_t half = s.length()/2;
        for (uint32_t i=0; i<s.length(); ++i)
        {
            if ( i < half ) { items.insert(s[i]); }
            else 
            { 
                if ( items.contains(s[i]) ) 
                {
                    result += get_priority(s[i]);
                    break;
                }
            }
        }
    });

    return result;
}

int main(int /*argc*/, char ** /*argv*/)
{
    timer t;
    auto result = perform("../inputs/day3.txt");
    std::cout << "day 3 part 1 result: " << result << " in " << t.elapsed_micro() << "us\n";

    return 0;
}
