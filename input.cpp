#include "input.hpp"

Input::Input(int history_capacity)
{
    this->history_capacity = history_capacity;
    this->history = std::deque<std::string>();
}

void Input::store_current_to_history()
{
    std::string s(input_buffer.begin(), input_buffer.end());
    if (input_buffer.size() == 0)
        return;
    input_buffer.clear();
    history_size += 1;
    if (history_size == history_capacity)
    {
        history.pop_back();
        history_size -= 1;
    }
    history.push_front(s);
    history_index = 0;
}

void Input::set_buffer_to_previous_input()
{
    if (history_size == 0)
    {
        return;
    }
    if (history_index == history_size)
    {
        std::string res = history.at(history_index - 1);
        input_buffer = std::vector<char>(res.begin(), res.end());
        return;
    }
    std::string res = history.at(history_index++);
    input_buffer = std::vector<char>(res.begin(), res.end());
}


void Input::add_one(char c)
{
    input_buffer.push_back(c);
}

void Input::remove_one()
{
    if (input_buffer.size() > 0) {
        input_buffer.pop_back();
    }
}

std::string Input::get_input_buffer()
{
    return std::string(input_buffer.begin(), input_buffer.end());
}

int Input::get_input_buffer_size()
{
    return input_buffer.size();
}
