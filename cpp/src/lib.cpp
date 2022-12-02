#include "lib.h"
#include<fstream>

std::vector<std::string> read_input(const std::string& input_filename)
{
    std::vector<std::string> result;
    std::ifstream ifs (input_filename, std::ifstream::in);
    std::string line;

    while ( getline(ifs, line) )
    {
        result.push_back(line);
    }
    return result;
}
