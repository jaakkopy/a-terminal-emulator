#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <X11/Xlib.h>

class WindowWrapper {
public:
    void setup_window();
    void handle_events();
private:
    Display *display;
    Window window;
    XEvent event;
    int default_screen;
    int x = 0;
    int y = 0;
    unsigned width = 800;
    unsigned height = 800;
    unsigned border_width = 0;
};


#endif