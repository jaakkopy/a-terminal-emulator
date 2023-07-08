#ifndef PTY_HPP
#define PTY_HPP

#include <sys/select.h>
#include <string>

class Shell {
public:
    void setup_pty();
    bool start_shell_process();
    void write_to_shell(char *buf, int amount_bytes);
    char read_from_shell();
    int get_primary_descriptor();
private:
    int primary;
    int secondary; 
    const char *secondary_name;
};

#endif