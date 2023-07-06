#include <X11/Xutil.h>
#include "event_handler.hpp"

EventHandler::EventHandler(std::shared_ptr<PTY> pty) {
    this->pty = pty;
}

void EventHandler::handle_event(XEvent event)
{
    if (event.type == KeyPress)
        handle_key_press((XKeyEvent*)&event);
}

void EventHandler::handle_key_press(XKeyEvent *event) {
    char buf[32];
    KeySym ksym;
    int num = XLookupString(event, buf, sizeof(buf), &ksym, 0);
    pty->write_to_shell_process(buf, num);
}
