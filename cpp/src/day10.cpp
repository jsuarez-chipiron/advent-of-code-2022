#include <iostream>
#include <vector>
#include <timer.h>
#include "lib.h"

std::vector<int32_t> calculate_instructions_vector(const std::string& input_filename)
{
    std::vector<int32_t> result;

    auto instrucctions = read_input(input_filename);
    int32_t xreg = 1;

    for ( const auto& instruction: instrucctions)
    {
        result.push_back(xreg);
        if ( instruction != "noop" )
        {
            auto inc = stoi(instruction.substr(5));
            result.push_back(xreg);
            xreg += inc;
        }
    }
    return result;
}

uint32_t perform(const std::string& input_filename)
{
    auto instructions_vector = calculate_instructions_vector(input_filename);
    auto result = 0;

    for ( int32_t val = 20; val <=220; val += 40 ) 
    {
        result += instructions_vector.at(val-1) * val;
    }

    return result;
}

int main(int /*argc*/, char ** /*argv*/)
{
    timer t;
    auto result = perform("../inputs/day10.txt");
    std::cout << "day 10 part 1 result: " << result << " in " << t.elapsed_micro() << "us\n";

    return 0;
}
