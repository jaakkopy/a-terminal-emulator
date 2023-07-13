#include <X11/Xutil.h>
#include <iostream>
#include <sys/select.h>
#include <cstring>
#include <errno.h>
#include "emulator.hpp"

Emulator::Emulator()
{
    input = std::make_unique<Input>(500);
    win = std::make_unique<Win>();
    shell = std::make_unique<Shell>();
}

void Emulator::run()
{
    shell->setup_pty();
    shell->start_shell_process();
    shell->adjust_window_size(win->get_width(), win->get_height());
    XEvent event;
    fd_set fds;
    int display_descriptor = win->get_display_descriptor();
    int primary = shell->get_primary_descriptor();
    int select_check_upper_limit = (display_descriptor > primary ? display_descriptor : primary) + 1;

    while (keep_running)
    {
        FD_ZERO(&fds);
        FD_SET(primary, &fds);
        FD_SET(display_descriptor, &fds);
        if (select(select_check_upper_limit, &fds, NULL, NULL, NULL) == -1)
        {
            std::cerr << strerror(errno) << std::endl;
            exit(1);
        }
        // shell has content to read
        if (FD_ISSET(primary, &fds))
        {
            char c = shell->read_from_shell();
            win->buf_write_char(c);
        }
        // display has events
        if (FD_ISSET(display_descriptor, &fds))
        {
            while (XPending(win->get_disp()))
            {
                XNextEvent(win->get_disp(), &event);
                handle_event(event);
            }
        }
        win->draw_buf();
    }
}

void Emulator::handle_event(XEvent &event)
{
    switch (event.type)
    {
    case KeyPress:
        handle_key_press_event(event.xkey);
        break;
    case ConfigureNotify:
        handle_configure_event(event.xconfigure);
        break;
    case Expose:
        win->draw_buf();
        break;
    }
}

void Emulator::handle_key_press_event(XKeyEvent &event)
{
    char buf[32];
    KeySym ksym;
    int num = XLookupString(&event, buf, sizeof(buf), &ksym, 0);
    shell->write_to_shell(buf, num);
    
    if (ksym == XK_Return)
    {
        input->store_current_to_history();
    }
    else if (ksym == XK_Up)
    {
        int current_size = input->get_input_buffer().size();
        const std::string previous = input->get_previous();
        shell->write_n('\b', current_size);
        shell->write_to_shell(previous);
        //win->write_str(previous);
    }
    else if (ksym == XK_BackSpace)
    {
        input->remove_one();
    }
    else
    {
        input->add_one((char)ksym);
    }
}

void Emulator::handle_configure_event(XConfigureEvent &event)
{
    // check if the window size changed
    // TODO: implement the buffer size change
    if (event.width != win->get_width() || event.height != win->get_height())
    {
        win->set_width(event.width);
        win->set_height(event.height);
        win->draw_buf();
    }
}
