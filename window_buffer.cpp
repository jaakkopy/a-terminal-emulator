#include "window_buffer.hpp"

WinBuf::WinBuf()
{
    buf = std::vector<std::vector<char>>(height, std::vector<char>(width, 0));
}

void WinBuf::write_char(char c)
{
    col += 1;
    if (col == width) {
        col = 0;
        row += 1;
    }
    if (row == height) {
        // TODO: move the lines in the buffer
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

std::vector<std::vector<char>> WinBuf::get_buf()
{
    return buf;
}
