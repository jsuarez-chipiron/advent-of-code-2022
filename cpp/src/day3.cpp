#include <iostream>
#include "lib.h" 
#include <algorithm>
#include <functional>
#include <numeric>
#include <timer.h>
#include <array>
#include <utility>
#include <unordered_set>
#include <unordered_map>

uint32_t get_priority(uint32_t n)
{
    if ( n >= 97 )
    {
        return n-96;
    }
    return n-38;
}

std::string squeeze(const std::string& cad)
{
    std::string result;

    char prev_char = '0';
    for (char c : cad)
    {
        if ( c != prev_char ) { result += c; }
        prev_char = c;
    }

    return result;
}

uint32_t perform_part1(const std::string& input_filename)
{
    auto lines = read_input(input_filename);

    uint32_t result = 0;

    std::for_each(lines.begin(), lines.end(), [&result](const std::string& s) {
        // iterate over the chars. If is in the first half then add to a set
        // if is in the second half then stop when an item is in the set. This is the repeated.
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

uint32_t perform_part2(const std::string& input_filename)
{
    auto lines = read_input(input_filename);
    std::array<std::string*, 3> elves_group{};
    uint32_t result = 0;
    uint8_t index = 0;

    for (auto& line: lines)
    {
        std::sort(line.begin(), line.end()); // sort the ruskback
        line = squeeze(line); // remove repeated items

        elves_group.at(index) = &line;

        if ( index == 2 ) // when the index is 2 then a group of three elfs has been completed
        {
            std::unordered_map<char, uint32_t> repeat_map;
            for (const auto& elf: elves_group) // add to a map the count of item
            {
                for (char c: *elf)
                {
                    if ( repeat_map.contains(c) )
                    {
                        repeat_map[c] = ++repeat_map[c];
                    }
                    else
                    {
                        repeat_map.insert({c, 0});
                    }
                }
            }
            for (const auto& rep: repeat_map)
            {
                if ( rep.second == 2 ) // the item with 3 repetitions is the badge
                {
                    result += get_priority(rep.first);
                    break;
                }
            }
        }

        ++index;
        index = index % 3;

    }

    return result;
}

int main(int /*argc*/, char ** /*argv*/)
{
    timer t;
    auto result = perform_part1("../inputs/day3.txt");
    std::cout << "day 3 part 1 result: " << result << " in " << t.elapsed_micro() << "us\n";

    t.reset();
    result = perform_part2("../inputs/day3.txt");
    std::cout << "day 3 part 2 result: " << result << " in " << t.elapsed_micro() << "us\n";

    return 0;
}
