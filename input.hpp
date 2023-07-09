#ifndef INPUT_HPP
#define INPUT_HPP

#include <deque>
#include <string>
#include <vector>

class Input
{
public:
    Input(int history_capacity);
    void store_current_to_history();
    std::string get_previous();
    std::string get_next();
    void add_to_input_buffer(char c);
    std::string get_input_buffer();

private:
    std::vector<char> input_buffer;
    int history_index = 0;
    int history_size = 0;
    int history_capacity;
    std::deque<std::string> history;
};

#endif