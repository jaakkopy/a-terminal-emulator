#include <X11/Xlib.h>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <memory>
#include "pty.hpp"
#include "window.hpp"
#include "event_handler.hpp"

int main(void) {
    std::shared_ptr<PTY> pty = std::make_shared<PTY>();
    WindowWrapper win;
    EventHandler evh(pty);
    pty->setup();
    win.setup_window();
    win.receive_events(evh);
    return 0;
}