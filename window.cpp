#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <X11/Xutil.h>
#include <unistd.h>
#include "window.hpp"

Win::Win()
{
    display = XOpenDisplay(NULL);
    if (display == NULL)
    {
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

Win::~Win()
{
    XCloseDisplay(display);
}

int Win::get_display_descriptor()
{
    return display_descriptor;
}

void Win::draw_buf(const std::shared_ptr<WinBuf> win_buf)
{
    int pos_x = 0;
    int pos_y = 0;
    int step_x = width / win_buf->get_width();
    int step_y = height / win_buf->get_height();
    const std::vector<std::vector<char>> &buf = win_buf->get_buf();
    for (int r = 0; r < win_buf->get_height(); ++r) {
        pos_x = 0;
        for (int c = 0; c < win_buf->get_width(); ++c) {
            char sym = buf.at(r).at(c);
            std::cout << "Writing: " << sym << std::endl;
            if (sym != '\0')
            {
                XDrawString(display, window, graphics_context, pos_x, pos_y, &sym, 1);
            }
            pos_x += step_x;
        }
        pos_y += step_y;
    }
}