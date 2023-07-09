#include "window_buffer.hpp"

WinBuf::WinBuf() {
    buf = std::vector<std::vector<char>>(height, std::vector<char>(width, 4));
}

void WinBuf::write_char(char c) {
}

int WinBuf::get_width() {
    return width;
}

int WinBuf::get_height() {
    return height;
}

std::vector<std::vector<char>> WinBuf::get_buf() {
    return buf;
}
