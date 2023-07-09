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
    XSelectInput(display, window, ExposureMask | KeyPressMask | StructureNotifyMask);
    XMapWindow(display, window);
    
    graphics_context = XCreateGC(display, window, 0, 0);
    XSetForeground(display, graphics_context, WhitePixel(display, default_screen));
    display_descriptor = ConnectionNumber(display);
    XSync(display, False);
}

Win::~Win() {
    XCloseDisplay(display);
}

int Win::get_display_descriptor() {
    return display_descriptor;
}

void Win::draw_buf(const std::vector<std::vector<char>> &buf) {
}