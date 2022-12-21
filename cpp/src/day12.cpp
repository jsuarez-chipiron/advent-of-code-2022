#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <timer.h>
#include "lib.h"

struct coord
{
    size_t x;
    size_t y;

    coord(size_t _x, size_t _y): x(_x), y(_y) {}
    
    void print() const
    {
        std::cout << "X: " << x << " Y: " << y << '\n';
    }
};

template<std::size_t F, std::size_t C>
struct monitoring
{
    std::array<std::array<char, C>, F> table;
    bool enabled = false;

    monitoring() 
    {
        for (size_t y=0; y<F; ++y)
        {
            for (size_t x=0; x<C; ++x)
            {
                table.at(y).at(x) = '.';
            }
        }
    }

    void print(uint32_t indent) const
    {
        if ( enabled )
        {
            for (size_t y=0; y<F; ++y)
            {
                for (size_t i=0; i<indent; ++i) { std::cout << ' '; }
                for (size_t x=0; x<C; ++x)
                {
                    std::cout << table.at(y).at(x) << ' ';
                }
                std::cout << '\n';
            }
        }
    }
};


template<std::size_t F, std::size_t C>
struct board
{
    std::array<std::array<char, C>, F> table;

    explicit board(const std::string& input_filename)
    {
        auto lines = read_input(input_filename);
        size_t y = 0;
        for (const auto& line: lines)
        {
            for (size_t x=0; x<C; ++x)
            {
                table.at(y).at(x) = line.at(x);
            }
            ++y;
        }
    }

    coord find_point(char val) const
    {
        for (size_t y=0; y<C; ++y)
        {
            for (size_t x=0; x<C; ++x)
            {
                if ( table.at(y).at(x) == val)
                {
                    return {x, y};
                }
            }
        }
        return {1000, 1000};
    }

    coord find_start() const
    {
        return find_point('S');
    }

    coord find_end() const
    {
        return find_point('E');
    }

    void find_path(const coord& c, uint32_t steps, std::array<std::array<bool, C>, F> visited, std::vector<uint32_t>& results, monitoring<F, C> mon) //NOLINT
    {
        auto current = table.at(c.y).at(c.x);
        visited.at(c.y).at(c.x) = true;

        if ( current == '{' ) 
        { 
            results.push_back(steps);
            return;
        }

        // std::cout << "current: " << current << " -- (" << c.y << ", " << c.x << ") -- steps:" << steps << "\n";

        if ( current == 'S' ) { current = 'a'; }

        auto nx = c.x+1;
        if ( nx < C && table.at(c.y).at(nx) >= current-1 && table.at(c.y).at(nx) <= current+1 && !visited.at(c.y).at(nx) )
        {
            mon.table.at(c.y).at(c.x) = '>';
            mon.print(steps);
            find_path(coord(nx, c.y), steps+1, visited, results, mon);
        }

        auto px = c.x-1;
        if ( px >= 0 && px < 8 && table.at(c.y).at(px) >= current-1 && table.at(c.y).at(px) <= current+1 && !visited.at(c.y).at(px) ) 
        {
            mon.table.at(c.y).at(c.x) = '<';
            mon.print(steps);
            find_path(coord(px, c.y), steps+1, visited, results, mon);
        }

        auto ny = c.y+1;
        if ( ny < F && table.at(ny).at(c.x) >= current-1 && table.at(ny).at(c.x) <= current+1 && !visited.at(ny).at(c.x) )
        {
            mon.table.at(c.y).at(c.x) = 'v';
            mon.print(steps);
            find_path(coord(c.x, ny), steps+1, visited, results, mon);
        }

        auto py = c.y-1;
        if ( py >=0 && py < F && table.at(py).at(c.x) >= current-1 && table.at(py).at(c.x) <= current+1 && !visited.at(py).at(c.x) )
        {
            mon.table.at(c.y).at(c.x) = 'A';
            mon.print(steps);
            find_path(coord(c.x, py), steps+1, visited, results, mon);
        }
    }

    void print() const
    {
        for (size_t y=0; y<F; ++y)
        {
            for (size_t x=0; x<C; ++x)
            {
                std::cout << table.at(y).at(x) << ' ';
            }
            std::cout << '\n';
        }
    }
};

template<std::size_t F, std::size_t C>
uint32_t perform(const std::string& input_filename, bool monitoring_enabled)
{
    board<F, C> b(input_filename);
    // board<41, 132> b("/home/javier/Tech/c++/advent-of-code/advent-of-code-2022/cpp/inputs/day12.txt");

    auto start = b.find_start();
    b.table.at(start.y).at(start.x) = 'a'; // this char is the prev to a
    auto end = b.find_end();
    b.table.at(end.y).at(end.x) = '{'; // this char is the next to z

    std::array<std::array<bool, C>, F> visited{};
    // std::array<std::array<bool, 132>, 41> visited{};

    monitoring<F, C> mon;
    mon.enabled = monitoring_enabled;
    mon.table.at(end.y).at(end.x) = '*';

    std::vector<uint32_t> results;
    b.find_path(start, 0, visited, results, mon);

    std::sort(results.begin(), results.end());

    return results.at(0);
}

int main(int /*argc*/, char ** /*argv*/)
{
    timer t;
    auto result = perform<5, 8>("../inputs/day12_sample.txt", true);
    // auto result = perform<41, 132>("../inputs/day12.txt", false);

    std::cout << "day 12 part 1 result: " << result << " in " << t.elapsed_micro() << "us\n";

    return 0;
}
