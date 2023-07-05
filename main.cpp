#include <X11/Xlib.h>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include "pty.hpp"
#include "window.hpp"

int main(void) {
    PTY pty;
    pty.setup();
    WindowWrapper win;
    win.setup_window();
    win.handle_events();
    return 0;
}