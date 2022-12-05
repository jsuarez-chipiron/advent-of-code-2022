#include <iostream>
#include <stack>
#include <array>
#include <functional>
#include <timer.h>
#include "lib.h"

std::array<std::stack<char>, 9> init_structure(const std::vector<std::string>& lines)
{
    std::array<std::stack<char>, 9> result;

    for (auto line: lines)
    {
        if ( line[0] != '[' )
        {
            break;
        }
        std::string padline = line.append("                                   ");

        for (size_t i=0; i<9; ++i)
        {
            size_t index = 4*i+1;
            if ( padline.at(index) != ' ' )
            {
                result.at(i).push(padline.at(index));
            }
        }
    }

    // reverse the stacks
    for (auto& stack: result)
    {
        std::stack<char> aux;
        while ( !stack.empty() )
        {
            aux.push(stack.top());
            stack.pop();
        }
        stack = aux;
    }

    return result;
}

std::array<uint32_t, 3> parse_command(std::string& line)
{
    std::array<uint32_t, 3> command{};
    line = line.substr(5);
    auto pos = line.find(' ');
    command[0] = stoi(line.substr(0,pos));
    line = line.substr(pos+6);
    pos = line.find(' ');
    command[1] = stoi(line.substr(0,pos));
    line = line.substr(pos+4);
    command[2] = stoi(line);

    return command;
}

void execute_command_9000(std::array<std::stack<char>, 9>& stacks, const std::array<uint32_t, 3>& command)
{
    for (size_t i=0; i<command[0]; ++i)
    {
        stacks.at(command[2]-1).push(stacks.at(command[1]-1).top());
        stacks.at(command[1]-1).pop();
    }
}
void execute_command_9001(std::array<std::stack<char>, 9>& stacks, const std::array<uint32_t, 3>& command)
{
    std::stack<char> memory;

    for (size_t i=0; i<command[0]; ++i)
    {
        memory.push(stacks.at(command[1]-1).top());
        stacks.at(command[1]-1).pop();
    }

    while ( !memory.empty() )
    {
        stacks.at(command[2]-1).push(memory.top());
        memory.pop();
    }
}


std::string perform(const std::string& input_filename, 
        const std::function<void(std::array<std::stack<char>, 9>&, 
            const std::array<uint32_t, 3>&)>& executor)
{
    auto lines = read_input(input_filename);
    auto stacks = init_structure(lines);

    for (auto& line: lines)
    {
        if ( line[0] == 'm' )
        {
            executor(stacks, parse_command(line));
        }
    }

    std::string result;
    for (const auto& stack: stacks)
    {
        result += stack.top();
    }

    return result;
}

int main(int /*argc*/, char ** /*argv*/)
{
    timer t;
    auto result = perform("../inputs/day5.txt", execute_command_9000);
    std::cout << "day 5 part 1 result: " << result << " in " << t.elapsed_micro() << "us\n";

    t.reset();
    result = perform("../inputs/day5.txt", execute_command_9001);
    std::cout << "day 5 part 2 result: " << result << " in " << t.elapsed_micro() << "us\n";

    return 0;
}
