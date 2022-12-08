#include <iostream>
#include <vector>
#include "lib.h"

void perform(const std::string& input_filename)
{
    const auto treemap = read_input(input_filename);
    const size_t treemap_size = treemap.size();

    std::vector<size_t> last_visible_l{};
    last_visible_l.reserve(treemap_size);

    for (const auto& line: treemap)
    {
        std::cout << "line: " << line << '\n';
        auto prev = line[0];
        size_t i = 1;
        while ( i < treemap_size)
        {
            if ( prev >= line.at(i) )
            {
                std::cout << "i: " << i-1 << '\n';
                last_visible_l.push_back(--i);
                break;
            }
            prev = line.at(i);
            ++i;
        }
    }

    std::cout << '\n';

    std::vector<size_t> last_visible_r{};
    last_visible_r.reserve(treemap_size);

    for (const auto& line: treemap)
    {
        std::cout << "line: " << line << '\n';
        auto prev = line.at(treemap_size-1);
        size_t i = treemap_size-2;
        while ( i >= 0)
        {
            if ( prev >= line.at(i) )
            {
                std::cout << "i: " << i+1 << '\n';
                last_visible_r.push_back(++i);
                break;
            }
            prev = line.at(i);
            --i;
        }
    }

    std::cout << '\n';

    std::vector<size_t> last_visible_t{};
    last_visible_t.reserve(treemap_size);

    for (size_t j=0; j<treemap_size; ++j)
    {
        auto prev = treemap.at(0).at(j);
        size_t i = 1;
        while ( i < treemap_size)
        {
            if ( prev >= treemap.at(i).at(j) )
            {
                std::cout << "i: " << i-1 << '\n';
                last_visible_t.push_back(--i);
                break;
            }
            prev = treemap.at(i).at(j);
            ++i;
        }
    }

    std::cout << '\n';

    std::vector<size_t> last_visible_b{};
    last_visible_b.reserve(treemap_size);

    for (size_t j=0; j<treemap_size; ++j)
    {
        auto prev = treemap.at(treemap_size-1).at(j);
        size_t i = treemap_size-2;
        while ( i >= 0 )
        {
            if ( prev >= treemap.at(i).at(j) )
            {
                std::cout << "i: " << i+1 << '\n';
                last_visible_b.push_back(++i);
                break;
            }
            prev = treemap.at(i).at(j);
            --i;
        }
    }

    bool check[treemap_size][treemap_size];

    for (size_t i=0; i<treemap_size; ++i)
    {
        for (size_t j=0; j<treemap_size; ++j)
        {
            check[i][j] = false;
        }
    }

    for (size_t i=0; i<treemap_size; ++i)
    {
        for (size_t j=0; j<treemap_size; ++j)
        {
            std::cout << treemap.at(i).at(j) << ' ';
            if ( j <= last_visible_l.at(i) )
            {
                check[i][j]=true;
            }
            if ( j >= last_visible_r.at(i) )
            {
                check[i][j]=true;
            }
        }
        std::cout << '\n';
    }

    std::cout << '\n';
    std::cout << '\n';

    for (size_t j=0; j<treemap_size; ++j)
    {
        for (size_t i=0; i<treemap_size; ++i)
        {
            // std::cout << treemap.at(i).at(j) << ' ';
            if ( j <= last_visible_t.at(i) )
            {
                check[j][i]=true;
            }
            if ( j >= last_visible_b.at(i) )
            {
                check[j][i]=true;
            }
        }
        std::cout << '\n';
    }

    uint32_t count = 0;
    for (size_t i=0; i<treemap_size; ++i)
    {
        for (size_t j=0; j<treemap_size; ++j)
        {
            if ( check[i][j] )
            {
                std::cout << "x ";
                count++;
            }
            else
            {
                std::cout << "o ";
            }
        }
        std::cout << '\n';
    }

    std::cout << "count: " << count << '\n';
}

int main(int /*argc*/, char ** /*argv*/)
{
    // perform("../inputs/day8.txt");
    perform("../inputs/day8_sample.txt");

    return 0;
}
