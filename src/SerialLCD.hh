// -*- mode: C++ -*-
// Time-stamp: "2012-09-14 00:13:00 sb"

/*
  file       SerialLCD.hh
  copyright  (c) Sebastian Blatt 2012

 */


#ifndef SERIALLCD_HH__22B313D7_4F6E_4801_90A2_DFD5E68F9910
#define SERIALLCD_HH__22B313D7_4F6E_4801_90A2_DFD5E68F9910

#include <string>
#include "Tty.hh"

class SerialLCD {
  private:
    static const unsigned char command_code;
    static const unsigned char ext_command_code;

    Tty tty;
  public:
    SerialLCD(const std::string& device);

    void WriteCharacter(unsigned char c);
    void WriteString(const std::string& s);
    void WriteCommand(unsigned char code);
    void Clear();
    void MoveCursor(unsigned char position, unsigned char line=0);
};


#endif // SERIALLCD_HH__22B313D7_4F6E_4801_90A2_DFD5E68F9910

// SerialLCD.hh ends here
