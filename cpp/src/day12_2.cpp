#include <iostream>
#include <array>
#include <algorithm>
#include <vector>
#include <timer.h>
#include "lib.h"

#define INF 9999999

struct coord
{
    size_t x;
    size_t y;
};

template<std::size_t F, std::size_t C>
struct board
{
    std::array<char, F*C> table;
    std::array<std::vector<uint32_t>, C*F> adj;
    std::array<int32_t, C*F> pq;
    std::array<uint32_t, C*F> dist;
    std::array<uint32_t, C*F> prev;

    uint32_t start;
    uint32_t end;

    explicit board(const std::string& input_filename)
    {
        auto lines = read_input(input_filename);
        int32_t i = 0;
        for (const auto& line: lines)
        {
            for (size_t x=0; x<C; ++x)
            {
                pq[i] = i; 
                dist[i] = INF;
                prev[i] = 0;
                table.at(i++) = line[x];
            }
        }
        start = find_start(); //NOLINT
        end = find_end(); //NOLINT

        dist[start] = 0;

        table[start] = 'a';
        table[end] = '{';

        calculate_adjacency_matrix();
        
        travel();
    }

    uint32_t find_point(char val) const
    {
        for (size_t i=0; i<C*F; ++i)
        {
            if ( table[i] == val )
            {
                return i;
            }
        }
        return INF;
    }

    uint32_t find_start() const
    {
        return find_point('S');
    }

    uint32_t find_end() const
    {
        return find_point('E');
    }

    uint32_t from_coord(const coord& c) const
    {
        return c.y*C+c.x;
    }

    coord from_idx(uint32_t idx)
    {
        uint32_t y = idx/C;
        uint32_t x = idx%C;
        return {x, y};
    }

    void calculate_adjacency_matrix()
    {
        for (size_t i=0; i<C*F; ++i)
        {
            auto orig = from_idx(i);

            //up
            auto ny = orig.y+1;
            if ( ny >= 0 && ny < F && table.at(from_coord({orig.x, ny})) <= table[i] + 1 )
            {
                adj[i].push_back(from_coord({orig.x, ny}));
            }

            //right
            auto nx = orig.x+1;
            if ( nx >= 0 && nx < C && table.at(from_coord({nx, orig.y})) <= table[i] + 1 )
            {
                adj[i].push_back(from_coord({nx, orig.y}));
            }

            ////down
            auto py = orig.y-1;
            if ( py >= 0 && py < F && table.at(from_coord({orig.x, py})) <= table[i] + 1 )
            {
                adj[i].push_back(from_coord({orig.x, py}));
            }

            //left
            auto px = orig.x-1;
            if ( px >= 0 && px < C && table.at(from_coord({px, orig.y})) <= table[i] + 1 )
            {
                adj[i].push_back(from_coord({px, orig.y}));
            }
        }
    }

    void travel()
    {
        while ( true )
        {
            uint32_t min = INF;
            int32_t selected = -1;
            for (int32_t i=0; i<pq.size(); ++i)
            {
                if ( pq[i] != -1 && dist[i] < min )
                {
                    min = dist[i];
                    selected = i;
                }
            }
            if ( min == INF || selected == -1 ) { break; }

            const auto& neighbours = adj[selected];
            for (const auto& i: neighbours) 
            { 
                if ( dist[i] > dist[selected] + 1 )
                {
                    dist[i] = dist[selected] + 1;
                    prev[i] = selected;
                }
            }
            pq[selected] = -1;
        }
    }

    void print() const
    {
        for (size_t i=0; i<F*C; ++i)
        {
            std::cout << table[i];
            if ( (i+1) % C == 0 ) { std::cout << '\n'; }
        }
    }
};

template <std::size_t F, std::size_t C>
uint32_t perform(const std::string& input_filename)
{
    board<F, C> b(input_filename);
    return b.dist[b.end];
}

int main(int /*argc*/, char ** /*argv*/)
{
    timer t;
    // auto result = perform<5, 8>("../inputs/day12_sample.txt");
    auto result = perform<41, 132>("../inputs/day12.txt");

    std::cout << "day 12 part 1 result: " << result << " in " << t.elapsed_micro() << "us\n";
    return 0;
}
