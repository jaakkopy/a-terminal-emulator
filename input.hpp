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
    void set_buffer_to_previous_input();
    void add_one(char c);
    void remove_one();
    std::string get_input_buffer();
    int get_input_buffer_size();

private:
    std::vector<char> input_buffer;
    int history_index = 0;
    int history_size = 0;
    int history_capacity;
    std::deque<std::string> history;
};

#endif