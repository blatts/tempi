// -*- mode: C++ -*-
// Time-stamp: "2012-09-14 14:17:42 sb"

/*
  file       Tty.cc
  copyright  (c) Sebastian Blatt 2012

 */

#include "Tty.hh"
#include "OutputManipulator.hh"

#include <sstream>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>


Tty::Tty(const std::string& device_)
  : fd(0),
    device(device_)
{
  // open tty device
  if((fd = open(device.c_str(), O_WRONLY)) < 0){
    std::ostringstream os;
    os << "open(\"" << device << "\", O_WRONLY) failed.\n"
       << "  " << strerror(errno);
    throw EXCEPTION(os.str());
  }
}

Tty::~Tty(){
  if(fd){
    close(fd);
  }
  fd = 0;
}

void Tty::Write(unsigned char c){
  int rc = 0;
  if((rc = write(fd, &c, 1)) != 1){
    std::ostringstream os;
    os << "write(" << hex_form<unsigned char>(c) << ") failed.\n"
       << "  " << strerror(errno);
    throw EXCEPTION(os.str());
  }
}

void Tty::Write(const std::string& s){
  int rc = 0;
  if((rc = write(fd, s.c_str(), s.size())) != s.size()){
    std::ostringstream os;
    os << "write(\"" << s << "\") failed.\n"
       << "  " << strerror(errno);
    throw EXCEPTION(os.str());
  }
}

speed_t Tty::GetOutputBaudRate(){
  // get current baud rate
  struct termios t;
  memset(&t, 0, sizeof(t));
  if(tcgetattr(fd, &t) < 0){
    std::ostringstream os;
    os << "tcgetattr(" << hex_form<int>(fd) << ") failed.\n"
       << "  " << strerror(errno);
    throw EXCEPTION(os.str());
  }
  return cfgetospeed(&t);
}

void Tty::SetOutputBaudRate(speed_t speed){
  // get current baud rate
  struct termios t;
  memset(&t, 0, sizeof(t));
  if(tcgetattr(fd, &t) < 0){
    std::ostringstream os;
    os << "tcgetattr(" << hex_form<int>(fd) << ") failed.\n"
       << "  " << strerror(errno);
    throw EXCEPTION(os.str());
  }

  // set baud rate to speed if not set already
  if(cfgetospeed(&t) != speed){
    if(cfsetospeed(&t, speed) < 0){
      std::ostringstream os;
      os << "cfsetospeed(" << speed << ") failed.\n"
         << "  " << strerror(errno);
      throw EXCEPTION(os.str());
    }
  }
  if(tcsetattr(fd, TCSANOW, &t) < 0){
    std::ostringstream os;
    os << "tcsetattr(" << hex_form<int>(fd) << ") failed.\n"
       << "  " << strerror(errno);
    throw EXCEPTION(os.str());
  }
}


// Tty.cc ends here
