#include <iostream>
#include <algorithm>
#include <numeric>
#include "lib.h"
#include <timer.h>

std::vector<std::vector<uint32_t>> partition(const std::vector<uint32_t>& v)
{
    std::vector<std::vector<uint32_t>> r;
    std::vector<uint32_t> p;
    std::for_each(v.begin(), v.end(), [&p, &r](uint32_t i) { 
        if ( i != 0 ) { p.push_back(i); }
        if ( i == 0 ) 
        {
            r.push_back(p);
            p = {};
        }
    });
    if ( !p.empty() )
    {
        r.push_back(p);
    }

    return r;
}

int main(int /*argc*/, char ** /*argv*/)
{
    timer t;
    auto v = read_input("../inputs/day1.txt");

    std::vector<uint32_t> cals;

    std::transform(v.begin(), v.end(), std::back_inserter(cals), [](const std::string& i) {
        if ( i.empty() ) { return 0; }
        return stoi(i);
    });

    auto p = partition(cals);

    std::vector<uint32_t> sum;
    std::transform(p.begin(), p.end(), std::back_inserter(sum), [](const std::vector<uint32_t>& i) {
        uint32_t ret = std::accumulate(i.begin(), i.end(), 0);
        return ret;
    });

    std::sort(sum.begin(), sum.end());

    std::cout << sum[sum.size()-1] << '\n';
    std::cout << sum[sum.size()-1] + sum[sum.size()-2] + sum[sum.size()-3] << '\n';

    std::cout << t.elapsed_micro() << "us\n";
    return 0;
}
