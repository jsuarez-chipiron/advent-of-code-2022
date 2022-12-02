#include <iostream>
#include <fstream>
#include <unordered_map>
#include <timer.h>

uint32_t perform(const std::string& input_filename)
{
    uint32_t total = 0;

    std::unordered_map<std::string, uint32_t> game_map =
    {
        {"A X", 4},
        {"A Y", 8},
        {"A Z", 3},
        {"B X", 1},
        {"B Y", 5},
        {"B Z", 9},
        {"C X", 7},
        {"C Y", 2},
        {"C Z", 6}
    };
    std::ifstream ifs (input_filename, std::ifstream::in);
    std::string line;

    while ( getline(ifs, line) )
    {
        // std::cout << game_map[line] << '\n';
        total += game_map[line];
    }

    return total;
}

int main(int /*argc*/, char ** /*argv*/)
{
    timer t;
    auto result = perform("../inputs/day2.txt");
    std::cout << "day 1 part 1 result: " << result << " in " << t.elapsed_micro() << "us\n";
    return 0;
}
