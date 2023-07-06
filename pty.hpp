#ifndef PTY_HPP
#define PTY_HPP

class PTY {
public:
    void setup();
    bool start_shell_process();
    void write_to_shell_process(char *buf, int amount_bytes);
private:
    int primary;
    int secondary; 
    const char *secondary_name;
};

#endif