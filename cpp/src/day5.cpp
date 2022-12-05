#include <iostream>
#include <stack>
#include <array>
#include <functional>
#include <timer.h>
#include "lib.h"

std::array<std::stack<char>, 9> init_structure()
{
    std::array<std::stack<char>, 9> result;

    result[0].push('D');
    result[0].push('T');
    result[0].push('W');
    result[0].push('F');
    result[0].push('J');
    result[0].push('S');
    result[0].push('H');
    result[0].push('N');

    result[1].push('H');
    result[1].push('R');
    result[1].push('P');
    result[1].push('Q');
    result[1].push('T');
    result[1].push('N');
    result[1].push('B');
    result[1].push('G');

    result[2].push('L');
    result[2].push('Q');
    result[2].push('V');

    result[3].push('N');
    result[3].push('B');
    result[3].push('S');
    result[3].push('W');
    result[3].push('R');
    result[3].push('Q');

    result[4].push('N');
    result[4].push('D');
    result[4].push('F');
    result[4].push('T');
    result[4].push('V');
    result[4].push('M');
    result[4].push('B');

    result[5].push('M');
    result[5].push('D');
    result[5].push('B');
    result[5].push('V');
    result[5].push('H');
    result[5].push('T');
    result[5].push('R');
    
    result[6].push('D');
    result[6].push('B');
    result[6].push('Q');
    result[6].push('J');

    result[7].push('D');
    result[7].push('N');
    result[7].push('J');
    result[7].push('V');
    result[7].push('R');
    result[7].push('Z');
    result[7].push('H');
    result[7].push('Q');

    result[8].push('B');
    result[8].push('N');
    result[8].push('H');
    result[8].push('M');
    result[8].push('S');

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
    auto stacks = init_structure();
    auto lines = read_input(input_filename);

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
