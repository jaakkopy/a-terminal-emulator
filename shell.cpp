#include <iostream>
#include <cstdlib>
#include <fcntl.h>
#include <errno.h>
#include <cstring>
#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>
#include "shell.hpp"

void Shell::setup_pty()
{
    primary = posix_openpt(O_RDWR | O_NOCTTY);
    if (primary == -1)
        goto pty_setup_fail;
    if (grantpt(primary) == -1)
        goto pty_setup_fail;
    if (unlockpt(primary) == -1)
        goto pty_setup_fail;
    if ((secondary_name = ptsname(primary)) == NULL)
        goto pty_setup_fail;
    if ((secondary = open(secondary_name, O_RDWR | O_NOCTTY)) == -1)
        goto pty_setup_fail;
    return;
pty_setup_fail:
    std::cerr << strerror(errno) << std::endl;
    exit(1);
}

bool Shell::start_shell_process()
{
    pid_t p = fork();
    if (p == 0)
    {
        close(primary);
        setsid();
        if (ioctl(secondary, TIOCSCTTY, NULL) == -1)
        {
            std::cerr << strerror(errno) << std::endl;
            return false;
        }
        dup2(secondary, STDIN_FILENO);
        dup2(secondary, STDOUT_FILENO);
        dup2(secondary, STDERR_FILENO);
        close(secondary);
        // char *env[] = { "TERM=vt100", NULL };
        char *env[] = {"TERM=dumb", NULL}; // TERM=dumb prevents ANSI code sequences. Better for now
        execle("/bin/bash", "-/bin/bash", (char *)NULL, env);
        return false;
    }
    else if (p > 0)
    {
        close(secondary);
        return true;
    }
    std::cerr << "fork failed" << std::endl;
    return false;
}

void Shell::write_to_shell(char *buf, int amount_bytes)
{
    for (int i = 0; i < amount_bytes; ++i)
    {
        write(primary, &buf[i], 1);
    }
}

char Shell::read_from_shell()
{
    char buf[1];
    if (read(primary, buf, 1) <= 0)
    {
        exit(1);
    }
    std::cout << "From shell: " << buf[0] << std::endl;
    return buf[0];
}

int Shell::get_primary_descriptor()
{
    return primary;
}

void Shell::adjust_window_buffer_size(int width, int height)
{
    struct winsize ws;
    ws.ws_col = width;
    ws.ws_row = height;
    if (ioctl(primary, TIOCSWINSZ, &ws) == -1)
    {
        std::cerr << strerror(errno) << std::endl;
    }
}
