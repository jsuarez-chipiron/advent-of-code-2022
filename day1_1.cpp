#include <iostream>
#include <fstream>

uint32_t get_elf_with_bigger_load(const std::string& input_filename)
{
    std::ifstream ifs (input_filename, std::ifstream::in);
    std::string line;

    uint32_t max_load = 0;
    uint32_t current_elf_load = 0;

    while ( getline(ifs, line) )
    {
        if ( line.empty() )
        {
            if ( current_elf_load > max_load )
            {
                max_load = current_elf_load;
            }
            current_elf_load = 0;
        }
        else
        {
            uint32_t n = stoi(line);
            current_elf_load += n;
        }
    }

    if ( current_elf_load != 0 && current_elf_load > max_load )
    {
        max_load = current_elf_load;
    }

    return max_load;
}

int main(int /*argc*/, char ** /*argv*/)
{
    auto result = get_elf_with_bigger_load("../inputs/day1.txt");

    std::cout << "day 1 part 1 result: " << result << '\n';

    return 0;
}
