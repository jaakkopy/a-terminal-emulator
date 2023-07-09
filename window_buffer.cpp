#include "window_buffer.hpp"

WinBuf::WinBuf()
{
    buf = std::deque<std::deque<char>>(height, std::deque<char>(width, 0));
}

void WinBuf::write_char(char c)
{
    ++col;
    if (col == width) {
        col = 0;
        ++row;
    }
    if (row == height) {
        // remove the first row and add a new one to the end 
        buf.pop_front();
        buf.push_back(std::deque<char>(width, 0));
        --row;
    }
    buf.at(row).at(col) = c;
}

int WinBuf::get_width()
{
    return width;
}

int WinBuf::get_height()
{
    return height;
}

std::deque<std::deque<char>> WinBuf::get_buf()
{
    return buf;
}
