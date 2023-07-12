#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <vector>
#include <X11/Xlib.h>
#include <memory>
#include <deque>
#include <string>

class Win
{
public:
    Win();
    ~Win();
    int get_display_descriptor();
    void draw_buf();
    int get_width() { return width; };
    int get_height() { return height; };
    void set_width(int w) { width = w; };
    void set_height(int h) { height = h; };
    Display *get_disp() { return display; };
    Window *get_win() { return &window; };
    void buf_write_char(char c);
    void write_n(char sym, int amount);
    void write_str(const std::string &s);
private:
    Display *display = nullptr;
    Window window;
    Window root_window;
    XFontStruct *font;
    int font_width, font_height;
    unsigned long bg_color, fg_color;
    int width, height;
    int display_descriptor;
    GC graphics_context;
    int default_screen;
    int x = 0;
    int y = 0;
    int buf_row = 0;
    int buf_col = 0;
    int buffer_width = 160;
    int buffer_height = 50;
    std::deque<std::deque<char>> buf;
};

#endif