// -*- mode: C++ -*-
// Time-stamp: "2012-09-14 14:17:37 sb"

/*
  file       Tty.hh
  copyright  (c) Sebastian Blatt 2012

 */


#ifndef TTY_HH__A40DC7D7_D817_4DC9_B282_24AD5A319203
#define TTY_HH__A40DC7D7_D817_4DC9_B282_24AD5A319203

#include <string>
#include <termios.h>
#include "Exception.hh"

class Tty {
  private:
    int fd;
    const std::string device;
  public:
    Tty(const std::string& device_);
    ~Tty();

    void Write(unsigned char c);
    void Write(const std::string& s);
    speed_t GetOutputBaudRate();
    void SetOutputBaudRate(speed_t speed);
};


#endif // TTY_HH__A40DC7D7_D817_4DC9_B282_24AD5A319203

// Tty.hh ends here
