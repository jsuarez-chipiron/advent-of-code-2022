#include <iostream>
#include <string_view>
#include <array>
#include <timer.h>
#include "lib.h"

std::array<uint32_t, 4> parse_line(std::string_view sv)
{
    std::string_view part1 = sv.substr(0, sv.find('-'));
    std::string_view rest = sv.substr(sv.find('-')+1);
    std::string_view part2 = rest.substr(0, rest.find(','));
    rest = rest.substr(rest.find(',')+1);
    std::string_view part3 = rest.substr(0, rest.find('-'));
    std::string_view part4 = rest.substr(rest.find('-')+1);

    std::array<uint32_t, 4> result{};
    result[0] = atoi(part1.data()); //NOLINT
    result[2] = atoi(part3.data()); //NOLINT 
    result[3] = atoi(part4.data()); //NOLINT
    result[1] = atoi(part2.data()); //NOLINT 

    return result;
}

bool contained(std::array<uint32_t, 4> sections)
{
    return ( sections[0] <= sections[2] && sections[1] >= sections[3] ) ||
         ( sections[2] <= sections[0] && sections[3] >= sections[1] );
}

uint32_t perform(const std::string& input_filename)
{
    auto lines = read_input(input_filename);
    uint32_t result = 0;

    for (std::string_view line: lines)
    {
        auto sections = parse_line(line);

        if ( contained(sections) )
        {
            ++result;
        }
    }
    return result;
}

int main(int /*argc*/, char ** /*argv*/)
{
    timer t;
    auto result = perform("../inputs/day4.txt");
    std::cout << "day 4 part 1 result: " << result << " in " << t.elapsed_micro() << "us\n";

    return 0;
}
