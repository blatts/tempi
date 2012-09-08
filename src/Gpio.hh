// -*- mode: C++ -*-
// Time-stamp: "2012-09-07 19:30:30 sb"

/*
  file       Gpio.hh
  copyright  (c) Sebastian Blatt 2012

 */


#ifndef GPIO_HH__D368AABC_A91E_4502_ADFD_D6FD92E7375D
#define GPIO_HH__D368AABC_A91E_4502_ADFD_D6FD92E7375D

class GPIO {
  private:
    volatile unsigned* gpio_ptr;
    int mem_fd;
    char* gpio_mem;
    char* gpio_map;
    char* spi0_mem;
    char* spi0_map;

    static const unsigned int page_size;
    static const unsigned int block_size;
    static const unsigned int BCM2708_peri_base;
    static const unsigned int gpio_base;

    static GPIO* singleton;
    GPIO();

  public:
    static GPIO& Instance();
    void SetInput(unsigned int pin);
    void SetOutput(unsigned int pin);
    void SetAlternative(unsigned int pin, unsigned int a);
};

#endif // GPIO_HH__D368AABC_A91E_4502_ADFD_D6FD92E7375D

// Gpio.hh ends here
