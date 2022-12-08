#include <iostream>
#include <vector>
#include <timer.h>
#include "lib.h"

std::vector<std::vector<int>> convert(const std::vector<std::string>& lines)
{
    std::vector<std::vector<int>> result;
    for(const auto& line: lines)
    {
        std::vector<int> row;
        for (size_t i=0; i<line.size(); ++i)
        {
            row.push_back(stoi(line.substr(i,1)));
        }
        result.push_back(row);
    }
    return result;
}

bool is_visible_1(const std::vector<std::vector<int>>& trees, size_t x, size_t y)
{
    auto current = trees.at(x).at(y);
    while ( x > 0 )
    {
        if ( trees.at(x-1).at(y) >= current )
        {
            return false;
        }
        --x;
    }
    return true;
}

bool is_visible_2(const std::vector<std::vector<int>>& trees, size_t x, size_t y)
{
    auto current = trees.at(x).at(y);
    while ( y > 0 )
    {
        if ( trees.at(x).at(y-1) >= current )
        {
            return false;
        }
        --y;
    }
    return true;
}

bool is_visible_3(const std::vector<std::vector<int>>& trees, size_t x, size_t y)
{
    auto size = trees.size();
    auto current = trees.at(x).at(y);
    while ( x < size-1 )
    {
        if ( trees.at(x+1).at(y) >= current )
        {
            return false;
        }
        ++x;
    }
    return true;
}

bool is_visible_4(const std::vector<std::vector<int>>& trees, size_t x, size_t y)
{
    auto size = trees.size();
    auto current = trees.at(x).at(y);
    while ( y < size-1 )
    {
        if ( trees.at(x).at(y+1) >= current )
        {
            return false;
        }
        ++y;
    }
    return true;
}

bool is_visible(const std::vector<std::vector<int>>& trees, size_t x, size_t y)
{
    auto size = trees.size();
    if ( x == 0 || y == 0 || x == size-1 || y == size-1 )
    {
        return true;
    }
    return is_visible_1(trees, x, y) || is_visible_2(trees, x, y) ||
        is_visible_3(trees, x, y) || is_visible_4(trees, x, y);
}

uint32_t perform(const std::string& input_filename)
{
    const auto treemap = read_input(input_filename);

    auto trees = convert(treemap);
    auto result = 0;

    for (size_t i=0; i<trees.size(); ++i)
    {
        for (size_t j=0; j<trees.at(i).size(); ++j)
        {
            if ( is_visible(trees, i, j) )
            {
                ++result;
            }
        }
    }

    return result;
}

int main(int /*argc*/, char ** /*argv*/)
{
    timer t;
    // perform("/home/javier/Tech/c++/advent-of-code/advent-of-code-2022/cpp/inputs/day8_sample.txt");
    auto result = perform("/home/javier/Tech/c++/advent-of-code/advent-of-code-2022/cpp/inputs/day8.txt");
    std::cout << "day 8 part 1 result: " << result << " in " << t.elapsed_micro() << "us\n";

    return 0;
}
