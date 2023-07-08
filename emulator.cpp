#include <X11/Xutil.h>
#include <iostream>
#include <sys/select.h>
#include <cstring>
#include <errno.h>
#include "emulator.hpp"

Emulator::Emulator() {
    input = std::make_unique<Input>(500);
    win = std::make_unique<Win>();
    shell = std::make_unique<Shell>();
}

void Emulator::run() {
    shell->setup_pty();
    shell->start_shell_process();
    XEvent event;
    fd_set fds;
    int display_descriptor = ConnectionNumber(win->display);
    int primary = shell->get_primary_descriptor();    
    int select_check_upper_limit = (display_descriptor > primary ? display_descriptor : primary) + 1;

    while (keep_running) {
        FD_ZERO(&fds);
        FD_SET(primary, &fds);
        FD_SET(display_descriptor, &fds);
        if (select(select_check_upper_limit, &fds, NULL, NULL, NULL) == -1) {
            std::cerr << strerror(errno) << std::endl;
            exit(1);
        }
        // shell has content to read
        if (FD_ISSET(primary, &fds)) {
            char c = shell->read_from_shell();
            XClearWindow(win->display, win->window);
            // test:
            win->draw_char(c);
        }
        // display has events
        if (FD_ISSET(display_descriptor, &fds)) {
            while (XPending(win->display)) {
                XNextEvent(win->display, &event);
                switch (event.type) {
                    case KeyPress:
                        handle_key_press_event(&event.xkey);
                        break;
                    case Expose:
                        break;
                }
            }
        }
    }
}

void Emulator::handle_key_press_event(XKeyEvent *event) {
    char buf[32];
    KeySym ksym;
    int num = XLookupString(event, buf, sizeof(buf), &ksym, 0);
    shell->write_to_shell(buf, num);
    if (ksym == XK_Return) {
        input->store_current_to_history();
    } else {
        input->add_to_input_buffer((char)ksym);
    }
}
