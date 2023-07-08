#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <X11/Xlib.h>

class Win {
public:
    Win();
    ~Win();
    void draw_str(const std::string s);
    void draw_char(char c);
    Display *display = nullptr;
    Window window;
private:
    GC graphics_context;
    int default_screen;
    int x = 0;
    int y = 0;
    unsigned width = 800;
    unsigned height = 800;
    unsigned border_width = 0;
};


#endif