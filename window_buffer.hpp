#ifndef WIN_BUF_HPP
#define WIN_BUF_HPP

#include <vector>

class WinBuf {
public:
    WinBuf();
    void write_char(char c);
    int get_width();
    int get_height();
    std::vector<std::vector<char>> get_buf();
private:
    int row = 0;
    int col = 0;
    int width = 80;
    int height = 25;
    std::vector<std::vector<char>> buf;
};

#endif