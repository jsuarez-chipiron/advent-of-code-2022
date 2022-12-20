#include <iostream>
#include <ranges>
#include <vector>
#include <unordered_map>
#include <functional>
#include <algorithm>
#include <timer.h>
#include "lib.h"

struct monkey
{
    uint32_t _id;
    uint32_t _inspections = 0;

    std::vector<uint32_t> _items;

    char _operation;
    uint32_t _operation_value;
    uint32_t _test = 0;
    uint32_t _throw_true = 0;
    uint32_t _throw_false = 0;

    uint32_t calculate_operation(uint32_t item_weight) const
    {
        if ( _operation == '+' )
        {
            return item_weight + this->_operation_value;
        }
        if ( _operation == '*' )
        {
            return item_weight * this->_operation_value;
        }
        return item_weight * item_weight;
    }

    void receive_item(uint32_t item)
    {
        _items.push_back(item);
    }

    void calculate_throws(std::unordered_map<uint32_t, monkey>& monkeys)
    {
        for (const auto& item: _items)
        {
            auto op_res = calculate_operation(item);

            auto receiver = _throw_false;
            op_res /= 3;
            if ( (op_res % _test) == 0 )
            {
                receiver = _throw_true;
            }
            ++_inspections;
            monkeys.at(receiver).receive_item(op_res);
        }

        _items = {};
    }
};

std::unordered_map<uint32_t, monkey> parse_input(const std::string& input_filename)
{
    std::unordered_map<uint32_t, monkey> result;

    auto lines = read_input(input_filename);

    for (auto it = lines.begin(); it != lines.end(); ++it)
    {
        monkey m = {};
        auto line = *it;
        uint32_t monkey_id = stoi(line.substr(7, 1));
        m._id = monkey_id;

        ++it;
        line = *it;

        auto items = line.substr(18);

        size_t pos = 0;
        std::string token;
        while ((pos = items.find(',')) != std::string::npos) {
            token = items.substr(0, pos);
            m._items.push_back(stoi(token));
            items.erase(0, pos + 1);
        }
        m._items.push_back(stoi(items));

        ++it;
        line = *it;

        m._operation = '+';

        if ( line.find('+') == std::string::npos )
        {
            m._operation = '*';
        }
        try
        {
            m._operation_value = stoi(line.substr(25));
        }
        catch (std::invalid_argument& ex)
        {
            m._operation = '$';
        }

        ++it;
        line = *it;
        m._test = stoi(line.substr(21));

        ++it;
        line = *it;
        m._throw_true = stoi(line.substr(29));

        ++it;
        line = *it;
        m._throw_false = stoi(line.substr(30));

        result.insert({monkey_id, m});

        ++it;
        if ( it == lines.end() )
        {
            break;
        }
    }

    return result;
}

uint32_t perform(const std::string& input_filename)
{
    auto monkeys = parse_input(input_filename);

    for (size_t i=0; i<20; ++i)
    {
        for (size_t j=0; j<monkeys.size(); ++j)
        {
            monkeys.at(j).calculate_throws(monkeys);
        }
    }

    std::vector<uint32_t> result_vector;
    result_vector.reserve(monkeys.size());

    for (const auto& monkey: monkeys)
    {
        result_vector.push_back(monkey.second._inspections);
    }

    std::sort(result_vector.begin(), result_vector.end());

    size_t i = 0;
    uint32_t result = 1;

    for (unsigned int partial : std::ranges::reverse_view(result_vector))
    {
        result *= partial;
        ++i;
        if ( i == 2 ) { return result; }
    }
    return 0;
}

int main(int /*argc*/, char ** /*argv*/)
{
    timer t;
    // auto result = perform("../inputs/day11_sample.txt");
    auto result = perform("../inputs/day11.txt");
    std::cout << "day 11 part 1 result: " << result << " in " << t.elapsed_micro() << "us\n";

    return 0;
}
