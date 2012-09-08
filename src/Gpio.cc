// -*- mode: C++ -*-
// Time-stamp: "2012-09-08 15:20:50 sb"

/*
  file       Gpio.cc
  copyright  (c) Sebastian Blatt 2012

 */

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cassert>
#include <cstring>

extern "C" {
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
}

#include "Gpio.hh"
#include "Exception.hh"
#include "OutputManipulator.hh"

GPIO* GPIO::singleton                      = NULL;
const unsigned int GPIO::page_size         = 4 * 1024;
const unsigned int GPIO::block_size        = 4 * 1024;
const unsigned int GPIO::BCM2708_peri_base = 0x20000000;
const unsigned int GPIO::gpio_base         = GPIO::BCM2708_peri_base + 0x200000;


GPIO::GPIO()
  : gpio_ptr(NULL),
    mem_fd(0),
    gpio_mem(NULL),
    gpio_map(NULL),
    spi0_mem(NULL),
    spi0_map(NULL)
{
  // Open /dev/mem
  if((mem_fd = open("/dev/mem", O_RDWR | O_SYNC)) < 0){
    std::ostringstream os;
    os << "open(\"/dev/mem\", O_RDWR | O_SYNC) failed.\n"
       << "  " << strerror(errno);
    throw EXCEPTION(os.str());
  }

  // memory map GPIO
  if((gpio_mem = (char*)malloc(block_size + (page_size-1))) == NULL){
    std::ostringstream os;
    os << "malloc(" << block_size + (page_size-1) << ") failed.\n"
       << "  " << strerror(errno);
    throw EXCEPTION(os.str());
  }
  // make sure pointer is on 4k boundary
  if((unsigned long)gpio_mem % page_size){
    gpio_mem += page_size - ((unsigned long)gpio_mem % page_size);
  }
  if((gpio_map = (char*)mmap((caddr_t)gpio_mem,
                             block_size,
                             PROT_READ | PROT_WRITE,
                             MAP_SHARED | MAP_FIXED,
                             mem_fd,
                             gpio_base)) == MAP_FAILED)
  {
    std::ostringstream os;
    os << "mmap(gpio_mem, " << hex_form<unsigned int>(gpio_base) << ") failed.\n"
       << "  " << strerror(errno);
    throw EXCEPTION(os.str());
  }

  gpio_ptr = (volatile unsigned*)gpio_map;

  for(unsigned int pin = 7; pin <= 11; ++pin){
    SetInput(pin);
    SetOutput(pin);
  }
}

GPIO& GPIO::Instance(){
  if(!singleton){
    GPIO* p = new GPIO();
    assert(p);
    return *p;
  }
  return *singleton;
}


void GPIO::SetInput(unsigned int pin){
  *(gpio_ptr + (pin/10)) &= ~(7 << ( (pin % 10) * 3 ));
}

void GPIO::SetOutput(unsigned int pin){
  *(gpio_ptr + (pin/10)) |=  (1 << ( (pin % 10) * 3 ));
}

void GPIO::SetAlternative(unsigned int pin, unsigned int a){
  *(gpio_ptr + (pin/10)) |= ((a<=3 ? a+4 : a==4 ? 3:2 ) << ((pin % 10) * 3));
}



// Gpio.cc ends here
