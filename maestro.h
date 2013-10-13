#ifndef __maestro__
#define __maestro__

#include <iostream>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include "servo.h"

struct MaestroException : public std::exception
{
    std::string s;
    MaestroException(std::string ss) : s(ss) {}
    ~MaestroException() throw () {}
    const char* what() const throw() { return s.c_str(); }
};

class Maestro {

private:
    const char* _device;
    int         _fd;

public:

    Maestro(const char* dev) : _device(dev) {
        _fd = open(_device, O_RDWR | O_NOCTTY);
        if (_fd == -1) {
            perror(_device);
            throw MaestroException("Invalid Device");
        }
    }
    ~Maestro() { close(_fd); }

    int goHome(Servo*);
    int getPosition(Servo*);
    int setPosition(Servo*, unsigned short);
    int stepUp(Servo*, int);
    int stepDown(Servo*, int);
    int getError(Servo*);
    bool isMoving(Servo*);


};

#endif
