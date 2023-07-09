#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <vector>
#include <X11/Xlib.h>

class Win {
public:
    Win();
    ~Win();
    int get_display_descriptor();
    void draw_buf(const std::vector<std::vector<char>> &buf);
    int get_width() {return width;};
    int get_height() {return height;};
    void set_width(int w) {width = w;};
    void set_height(int h) {height = h;};
    Display *get_disp() {return display;};
    Window *get_win() {return &window;};
private:
    Display *display = nullptr;
    Window window;
    int width = 800;
    int height = 800;
    int display_descriptor;
    GC graphics_context;
    int default_screen;
    int x = 0;
    int y = 0;
    unsigned border_width = 0;
};


#endif