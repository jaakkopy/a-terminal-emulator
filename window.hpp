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
};


#endif