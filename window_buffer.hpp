#ifndef WIN_BUF_HPP
#define WIN_BUF_HPP

#include <deque>

class WinBuf
{
public:
    WinBuf();
    void write_char(char c);
    int get_width();
    int get_height();
    std::deque<std::deque<char>> get_buf();

private:
    int row = 0;
    int col = 0;
    int width = 80;
    int height = 25;
    std::deque<std::deque<char>> buf;
};

#endif