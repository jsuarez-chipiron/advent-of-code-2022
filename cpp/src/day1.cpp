#include <iostream>
#include <fstream>
#include <array>
#include <numeric>
#include <functional>
#include <algorithm>
#include <timer.h>

void check_top_1(std::array<uint32_t, 1>& a, uint32_t cl)
{
    if ( cl > a[0] )
    {
        a[0] = cl;
    }
}

void check_top_3(std::array<uint32_t, 3>& a, uint32_t cl)
{
    for (size_t i=0; i<3; ++i)
    {
        if ( cl > a.at(i) )
        {
            for (size_t j=2; j>i; --j)
            {
                a.at(j) = a.at(j-1);
            }
            a.at(i) = cl;

            break;
        }
    }
}

template<std::size_t N>
uint32_t perform(const std::string& input_filename, 
        std::array<uint32_t, N> max_load, 
        std::function<void(std::array<uint32_t, N>&, uint32_t)> check)
{
    std::ifstream ifs (input_filename, std::ifstream::in);
    std::string line;

    uint32_t current_elf_load = 0;

    while ( getline(ifs, line) )
    {
        if ( line.empty() )
        {
            check(max_load, current_elf_load);
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
        check(max_load, current_elf_load);
    }

    return std::accumulate(max_load.begin(), max_load.end(), 0, [](uint32_t a, uint32_t b) {return a+b;});
}

int main(int /*argc*/, char ** /*argv*/)
{
    timer t;
    std::array<uint32_t, 1> top_one = {0};
    auto result = perform<1>("../inputs/day1.txt", top_one, check_top_1);
    std::cout << "day 1 part 1 result: " << result << " in " << t.elapsed_micro() << "us\n";

    t.reset();
    std::array<uint32_t, 3> top_elves = {0, 0, 0};
    result = perform<3>("../inputs/day1.txt", top_elves, check_top_3);
    std::cout << "day 1 part 2 result: " << result << " in " << t.elapsed_micro() << "us\n";

    return 0;
}
