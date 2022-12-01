#include <iostream>
#include <fstream>
#include <array>
#include <numeric>
#include <algorithm>

void check_iv_top_3(std::array<uint32_t, 3>& a, uint32_t cl)
{
    for (size_t i=0; i<3; ++i)
    {
        if ( cl > a[i] )
        {
            for (size_t j=2; j>i; --j)
            {
                a[j] = a[j-1];
            }
            a[i] = cl;

            break;
        }
    }
}

uint32_t get_elf_with_bigger_load(const std::string& input_filename)
{
    std::ifstream ifs (input_filename, std::ifstream::in);
    std::array<uint32_t, 3> top_elves = {0, 0, 0};
    std::string line;

    uint32_t current_elf_load = 0;

    while ( getline(ifs, line) )
    {
        if ( line.empty() )
        {
            check_iv_top_3(top_elves, current_elf_load);
            current_elf_load = 0;
        }
        else
        {
            uint32_t n = stoi(line);
            current_elf_load += n;
        }
    }

    if ( current_elf_load != 0 )
    {
        check_iv_top_3(top_elves, current_elf_load);
    }

    return std::accumulate(top_elves.begin(), top_elves.end(), 0, [](uint32_t a, uint32_t b) {return a+b;});
}

int main(int /*argc*/, char ** /*argv*/)
{
    auto result = get_elf_with_bigger_load("../inputs/day1.txt");

    std::cout << "day 1 part 2 result: " << result << '\n';

    return 0;
}
