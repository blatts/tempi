MAINTAINERCLEANFILES = Makefile.in
EXTRA_DIST =

bin_PROGRAMS = gpio_test
gpio_test_CXXFLAGS = #$(GSL_CFLAGS) $(HDF5_CFLAGS)
gpio_test_LDADD = #$(GSL_LIBS) $(HDF5_LIBS) #@CURSES_LIB@

noinst_HEADERS = \
  CommandLine.hh \
  Exception.hh \
  Representable.hh \
  StringVector.hh \
	OutputManipulator.hh \
	Validator.hh \
	Gpio.hh \
	Tty.hh \
	SerialLCD.hh

gpio_test_SOURCES = \
  CommandLine.cc \
  Representable.cc \
  StringVector.cc \
	Gpio.cc \
	Tty.cc \
	SerialLCD.cc \
	gpio_test.cc
