// -*- mode: C++ -*-
// Time-stamp: "2012-09-14 00:18:07 sb"

/*
  file       gpio_test.cc
  copyright  (c) Sebastian Blatt 2012

 */

#define PROGRAM_NAME         "gpio_test"
#define PROGRAM_DESCRIPTION  "Test GPIO pins on Raspberry Pi"
#define PROGRAM_COPYRIGHT    "(C) Sebastian Blatt 2012"
#define PROGRAM_VERSION      "20120914"

#include <iostream>

#include "CommandLine.hh"
#include "Gpio.hh"
#include "SerialLCD.hh"

static const char* program_options[] = {
  "Blarg", "blarg", "b", ""
  };

int main(int argc, char** argv){
  CommandLine cl(argc, argv);
  DWIM_CommandLine(cl,
                   PROGRAM_NAME,
                   PROGRAM_DESCRIPTION,
                   PROGRAM_VERSION,
                   PROGRAM_COPYRIGHT,
                   program_options,
                   sizeof(program_options)/sizeof(char*)/4);


  try{
    GPIO& gpio = GPIO::Instance();

    const std::string device = "/dev/ttyAMA0";
    SerialLCD lcd(device);
    lcd.Clear();
    lcd.MoveCursor(0, 1);
    lcd.WriteString("Hello world.");
  }
  catch(const Exception& e){
    std::cerr << e << std::endl;
    return 1;
  }

  return 0;
}

// gpio_test.cc ends here
