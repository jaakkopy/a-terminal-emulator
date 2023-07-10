#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <X11/Xutil.h>
#include <unistd.h>
#include "window.hpp"

Win::Win()
{
    buf = std::deque<std::deque<char>>(buffer_height, std::deque<char>(buffer_width, 0));
    XSetWindowAttributes wa;
    wa.background_pixmap = ParentRelative;
    wa.event_mask = KeyPressMask | KeyReleaseMask | ExposureMask | StructureNotifyMask;
    display = XOpenDisplay(NULL);
    if (display == NULL)
    {
        std::cerr << "error opening display" << std::endl;
        exit(1);
    }
    default_screen = DefaultScreen(display);
    root_window = RootWindow(display, default_screen);
    display_descriptor = ConnectionNumber(display);
    font = XLoadQueryFont(display, "fixed");
    if (font == NULL)
    {
        std::cerr << "error loading font" << std::endl;
        exit(1);
    }
    font_width = XTextWidth(font, "a", 1);
    font_height = font->ascent + font->descent;
    // Load black as background color
    XColor color;
    Colormap color_map = DefaultColormap(display, default_screen);
    if (!XAllocNamedColor(display, color_map, "#000000", &color, &color))
    {
        std::cerr << "error loading background color" << std::endl;
        exit(1);
    }
    bg_color = color.pixel;
    // Load green as the foreground color
    if (!XAllocNamedColor(display, color_map, "#008000", &color, &color))
    {
        std::cerr << "error loading foreground color" << std::endl;
        exit(1);
    }
    fg_color = color.pixel;
    width = buffer_width * font_width; 
    height = buffer_height * font_height; 
    window = XCreateWindow(
        display,            // display
        root_window,        // Parent window. Set to root
        0,                  // x position of top left corner
        0,                  // y position of top left corner
        width,              // window width and height 
        height, 
        0, 
        DefaultDepth(display, default_screen), 
        CopyFromParent, 
        DefaultVisual(display, default_screen), 
        CWBackPixmap | CWEventMask, 
        &wa);
    XStoreName(display, window, "terminal");
    XMapWindow(display, window);
    graphics_context = XCreateGC(display, window, 0, NULL);
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

void Win::draw_buf()
{
    // "Clear" the screen with a black square
    XSetForeground(display, graphics_context, bg_color);
    XFillRectangle(display, window, graphics_context, 0, 0, width, height);
    // Start drawing the letters. Set the foreground color
    XSetForeground(display, graphics_context, fg_color);
    for (int r = 0; r < buffer_height; ++r)
    {
        for (int c = 0; c < buffer_width; ++c)
        {
            char sym = buf.at(r).at(c);
            // skip the control characters
            if (!iscntrl(sym))
            {
                XDrawString(display, window, graphics_context, c * font_width, r * font_height + font->ascent, &sym, 1);
            }
        }
    }
    // Draw the cursor    
    XSetForeground(display, graphics_context, fg_color);
    XFillRectangle(display, window, graphics_context, (buf_col + 1) * font_width, buf_row * font_height, font_width, font_height);
    XSync(display, False);
}

void Win::buf_write_char(char c)
{
    ++buf_col;
    if (c == '\n')
    {
        buf_col = 0;
        ++buf_row;
    }
    else if (c == '\r')
    {
        buf_col = 0;
    }
    if (buf_col == buffer_width)
    {
        buf_col = 0;
        ++buf_row;
    }
    if (buf_row == buffer_height)
    {
        // remove the first row and add a new one to the end 
        buf.pop_front();
        buf.push_back(std::deque<char>(buffer_width, 0));
        --buf_row;
    }
    buf.at(buf_row).at(buf_col) = c;
}