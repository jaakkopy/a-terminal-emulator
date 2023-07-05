#ifndef PTY_HPP
#define PTY_HPP

class PTY {
public:
    void setup();
    bool start_shell_process();
private:
    int primary;
    int secondary; 
    const char *secondary_name;
};

#endif