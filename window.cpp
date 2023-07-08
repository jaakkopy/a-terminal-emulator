#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <X11/Xutil.h>
#include <unistd.h>
#include "window.hpp"

Win::Win() {
    display = XOpenDisplay(NULL);
    if (display == NULL) {
        std::cerr << "error opening display" << std::endl;
        exit(1);
    }
    default_screen = DefaultScreen(display);
    window = XCreateSimpleWindow(display, RootWindow(display, default_screen), x, y, width, height, border_width, BlackPixel(display, default_screen), BlackPixel(display, default_screen));
    XSelectInput(display, window, ExposureMask | KeyPressMask);
    XMapWindow(display, window);
    
    graphics_context = XCreateGC(display, window, 0, 0);
    XSetForeground(display, graphics_context, WhitePixel(display, default_screen));
}

Win::~Win() {
    XCloseDisplay(display);
}

void Win::draw_char(char c) {
    XDrawString(display, window, graphics_context, width/2, height/2, &c, 1);
}

void Win::draw_str(const std::string s) {
    XDrawString(display, window, graphics_context, width/2, height/2, s.c_str(), s.size());
}
