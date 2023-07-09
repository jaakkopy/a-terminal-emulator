#ifndef EMULATOR_HPP
#define EMULATOR_HPP

#include <memory>
#include "shell.hpp"
#include "window.hpp"
#include "window_buffer.hpp"
#include "input.hpp"

class Emulator {
public:
    Emulator();
    void run();
private:
    bool keep_running = true;
    const char *display_str;
    std::unique_ptr<Input> input;
    std::unique_ptr<Win> win;
    std::unique_ptr<WinBuf> win_buf;
    std::unique_ptr<Shell> shell;
    void handle_key_press_event(XKeyEvent *event);
    void handle_configure_event(XConfigureEvent *event);
};

#endif