#include "input.hpp"

Input::Input(int history_capacity) {
    this->history_capacity = history_capacity;
    this->history = std::deque<std::string>();
}

void Input::store_current_to_history() {
    std::string s(input_buffer.begin(), input_buffer.end());
    input_buffer.clear();
    if (input_buffer.size() == 0)
        return;
    history_size += 1;
    if (history_size >= history_capacity) {
        history.pop_back();
        history_size -= 1;
    }
    history.push_front(s);
}

std::string Input::get_previous() {
    int position = history_index + 1 < history_size ? history_index + 1 : history_size - 1;
    return history.at(position);
}

std::string Input::get_next() {
    int position = history_index - 1 >= 0 ? history_index - 1 : 0;
    return history.at(position);
}

void Input::add_to_input_buffer(char c) {
    input_buffer.push_back(c);
}

std::string Input::get_input_buffer() {
    return std::string(input_buffer.begin(), input_buffer.end());
}
