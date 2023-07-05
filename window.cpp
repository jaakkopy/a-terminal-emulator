#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include "window.hpp"

void WindowWrapper::setup_window() {
    display = XOpenDisplay(NULL);
    if (display == NULL) {
        std::cerr << "error opening display" << std::endl;
        exit(1);
    }
    default_screen = DefaultScreen(display);
    window = XCreateSimpleWindow(display, RootWindow(display, default_screen), 10, 10, 100, 100, 1, BlackPixel(display, default_screen), WhitePixel(display, default_screen));
    XSelectInput(display, window, ExposureMask | KeyPressMask);
    XMapWindow(display, window);
}

void WindowWrapper::handle_events() {
    while (1) {
        XNextEvent(display, &event);
        if (event.type == Expose) {
            XFillRectangle(display, window, DefaultGC(display, default_screen), 20, 20, 10, 10);
            XDrawString(display, window, DefaultGC(display, default_screen), 10, 50, "Hello", 5);
        }
        if (event.type == KeyPress)
            break;
    }
    XCloseDisplay(display);
}
