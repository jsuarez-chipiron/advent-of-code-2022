#include <iostream>
#include <utility>
#include <vector>
#include <stack>
#include <memory>
#include <timer.h>
#include <numeric>
#include "lib.h"

enum node_type
{
    dir,
    file
};

class node
{
public:
    explicit node(std::string name, node_type type): name_(std::move(name)), type_(type) {}

    node(std::string name, node_type type, int size): name_(std::move(name)), type_(type), size_(size) {}

    node(const node& rhs) = default;

    node(node&& rhs) = default;

    node& operator=(const node& rhs) = default;

    node& operator=(node&& rhs) = default;

    ~node() = default;

    [[nodiscard]] std::string get_name() const { return name_; }

    [[nodiscard]] node_type get_type() const { return type_; }

    [[nodiscard]] uint64_t get_size() const { return size_; }

    [[nodiscard]] std::vector<std::shared_ptr<node>>& get_nodes() { return nodes_; }

    [[nodiscard]] std::shared_ptr<node> find_dir_by_name(const std::string& name)
    {
        for (const auto& n: nodes_)
        {
            if ( n->get_type() == dir && n->get_name() == name )
            {
                return n;
            }
        }
        return nullptr;
    }

private:
    std::string name_;
    node_type type_;
    uint64_t size_{};
    std::vector<std::shared_ptr<node>> nodes_;
    
};

node parse_line(const std::string& line)
{
    if ( line[0] == 'd' )
    {
        return node(line.substr(4), dir);
    }
    size_t pos = line.find(' ');
    auto size = line.substr(0, pos);
    auto name = line.substr(pos+1);
    return {name, file, stoi(size)}; 
}

uint64_t calculate_size_dir(const std::shared_ptr<node>& ptr, std::vector<uint64_t>& result)
{
    uint64_t size = 0;
    for (const auto& i: ptr->get_nodes())
    {
        if ( i->get_type() == file )
        {
            size += i->get_size();
        }
        if ( i->get_type() == dir )
        {
            auto dir_size = calculate_size_dir(i, result);
            if ( dir_size <= 100000 )
            {
                result.push_back(dir_size);
            }
            size += dir_size;
        }
    }
    return size;
}

void explore_tree(const std::shared_ptr<node>& ptr, uint64_t level)
{
    for (const auto& i: ptr->get_nodes())
    {
        for (uint8_t i=0; i<level*4; ++i)
        {
            std::cout << ' ';
        }
        std::cout << i->get_name() << ": " << i->get_size() << '\n';
        if ( i->get_type() == dir )
        {
            explore_tree(i, ++level);
        }
    }
}

uint64_t perform(const std::string& input_filename)
{
    node root_node("root", dir);
    std::stack<std::shared_ptr<node>> dir_stack;
    auto root = std::make_shared<node>(root_node);
    dir_stack.push(root);

    auto lines = read_input(input_filename);

    size_t i = 1; //skip first line

    while (i<lines.size())
    {
        std::string line = lines[i];

        if ( line == "$ ls" )
        {
            ++i;
            if ( i == lines.size() )
            {
                break;
            }
            line = lines[i];
            dir_stack.top()->get_nodes().push_back(std::make_shared<node>(parse_line(line)));

            while ( line[0] != '$' )
            {
                ++i;
                if ( i == lines.size() )
                {
                    break;
                }
                line = lines[i];
                if ( line[0] != '$' )
                {
                    dir_stack.top()->get_nodes().push_back(std::make_shared<node>(parse_line(line)));
                }
            }
            if ( i >= lines.size() )
            {
                break;
            }
        }
        ++i;
        // the command is always a CD
        if ( line == "$ cd .." )
        {
            // go to upper dir
            dir_stack.pop();
        }
        else
        {
            // go to next dir
            auto dir_name = line.substr(5);
            auto new_dir = dir_stack.top()->find_dir_by_name(dir_name);
            dir_stack.push(new_dir);
        }
    }

    // explore_tree(root, 0);

    std::vector<uint64_t> result_vec;
    calculate_size_dir(root, result_vec);

    return std::accumulate(result_vec.begin(), result_vec.end(), 0);
}

int main(int /*argc*/, char ** /*argv*/)
{
    timer t;
    // auto result = perform("/home/javier/Tech/c++/advent-of-code/advent-of-code-2022/cpp/inputs/day7_sample.txt");
    auto result = perform("/home/javier/Tech/c++/advent-of-code/advent-of-code-2022/cpp/inputs/day7.txt");
    std::cout << "day 1 part 1 result: " << result << " in " << t.elapsed_micro() << "us\n";

    return 0;
}
