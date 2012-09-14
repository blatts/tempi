// -*- mode: C++ -*-
// Time-stamp: "2012-09-14 00:13:44 sb"

/*
  file       SerialLCD.cc
  copyright  (c) Sebastian Blatt 2012

 */

#include "SerialLCD.hh"

const unsigned char SerialLCD::command_code = 0x07;
const unsigned char SerialLCD::ext_command_code = 0xfe;


SerialLCD::SerialLCD(const std::string& device)
  : tty(device)
{}

void SerialLCD::WriteCharacter(unsigned char c){
  tty.Write(c);
}
void SerialLCD::WriteString(const std::string& s){
  tty.Write(s);
}
void SerialLCD::WriteCommand(unsigned char code){
  tty.Write(ext_command_code);
  tty.Write(code);
}
void SerialLCD::Clear(){
  WriteCommand(0x01);
}
void SerialLCD::MoveCursor(unsigned char position, unsigned char line){
  line %= 2;
  position %= 64;
  position += 64*line;
  position |= 1<<7;
  WriteCommand(position);
}


// SerialLCD.cc ends here
