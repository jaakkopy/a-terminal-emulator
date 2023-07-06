#include <iostream>
#include <cstdlib>
#include <fcntl.h>
#include <errno.h>
#include <cstring>
#include <unistd.h>
#include <sys/ioctl.h>
#include "pty.hpp"

void PTY::setup() {
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

bool PTY::start_shell_process() {
    pid_t p = fork();
    if (p == 0) {
        close(primary);
        setsid();
        if (ioctl(secondary, TIOCSCTTY, NULL) == -1) {
            std::cerr << strerror(errno) << std::endl;
            return false;
        }
        dup2(secondary, STDIN_FILENO);
        dup2(secondary, STDOUT_FILENO);
        dup2(secondary, STDERR_FILENO);
        close(secondary);
        char *env[] = { "TERM=vt100", NULL };
        execle("/bin/bash", "-/bin/bash", (char *)NULL, env);
        return false;
    } else if (p > 0) {
        close(secondary);
        return true;
    }
    std::cerr << "fork failed" << std::endl;
    return false;
}

void PTY::write_to_shell_process(char *buf, int amount_bytes) {
    for (int i = 0; i < amount_bytes; ++i) {
        write(primary, &buf[i], 1);
    }
}
