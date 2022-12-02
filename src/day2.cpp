#include <iostream>
#include <fstream>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <numeric>
#include <timer.h>
#include "lib.h"

uint32_t perform_iterative(const std::string& input_filename, const std::unordered_map<std::string, uint32_t>& map)
{
    uint32_t total = 0;

    std::ifstream ifs (input_filename, std::ifstream::in);
    std::string line;

    while ( getline(ifs, line) )
    {
        total += map.at(line);
    }

    return total;
}

uint32_t perform_functional(const std::string& input_filename, const std::unordered_map<std::string, uint32_t>& map)
{
    auto input = read_input(input_filename);
    std::vector<uint32_t> points = {};

    std::transform(input.begin(), input.end(), std::back_inserter(points), [&map](const auto& i) {
        return map.at(i);
    });

    return std::accumulate(points.begin(), points.end(), 0, [](uint32_t a, uint32_t b) {return a+b;});
}

int main(int /*argc*/, char ** /*argv*/)
{

    std::unordered_map<std::string, uint32_t> part1_map =
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

    std::unordered_map<std::string, uint32_t> part2_map =
    {
        {"A X", 3},
        {"A Y", 4},
        {"A Z", 8},
        {"B X", 1},
        {"B Y", 5},
        {"B Z", 9},
        {"C X", 2},
        {"C Y", 6},
        {"C Z", 7}
    };

    timer t;
    auto result = perform_iterative("../inputs/day2.txt", part1_map);
    std::cout << "day 1 part 1 *iterative* result: " << result << " in " << t.elapsed_micro() << "us\n";

    t.reset();
    result = perform_iterative("../inputs/day2.txt", part2_map);
    std::cout << "day 1 part 2 *iterative* result: " << result << " in " << t.elapsed_micro() << "us\n";

    t.reset();
    result = perform_functional("../inputs/day2.txt", part1_map);
    std::cout << "day 1 part 1 *functional* result: " << result << " in " << t.elapsed_micro() << "us\n";

    t.reset();
    result = perform_functional("../inputs/day2.txt", part2_map);
    std::cout << "day 1 part 2 *functional* result: " << result << " in " << t.elapsed_micro() << "us\n";

    return 0;
}
