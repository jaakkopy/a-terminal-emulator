#ifndef EVENT_HANDLER_HPP
#define EVENT_HANDLER_HPP

#include <X11/Xlib.h>
#include <memory>
#include "pty.hpp"

class EventHandler {
public:
    EventHandler(std::shared_ptr<PTY> pty);
    void handle_event(XEvent event);
private:
    std::shared_ptr<PTY> pty;
    void handle_key_press(XKeyEvent *event);
};


#endif