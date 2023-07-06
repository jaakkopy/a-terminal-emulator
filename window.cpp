#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <X11/Xutil.h>
#include <unistd.h>
#include "window.hpp"

void WindowWrapper::setup_window() {
    display = XOpenDisplay(NULL);
    if (display == NULL) {
        std::cerr << "error opening display" << std::endl;
        exit(1);
    }
    default_screen = DefaultScreen(display);
    window = XCreateSimpleWindow(display, RootWindow(display, default_screen), x, y, width, height, border_width, BlackPixel(display, default_screen), BlackPixel(display, default_screen));
    XSelectInput(display, window, ExposureMask | KeyPressMask);
    XMapWindow(display, window);
}

void WindowWrapper::receive_events(EventHandler &evh) {
    const char *test_str = "Hello!";
    GC test_graphics_context = XCreateGC(display, window, 0, 0);
    XSetForeground(display, test_graphics_context, WhitePixel(display, default_screen));
    while (1) {
        XNextEvent(display, &event);
        evh.handle_event(event);
        XDrawString(display, window, test_graphics_context, width/2, height/2, test_str, strlen(test_str));
    }
    XCloseDisplay(display);
}