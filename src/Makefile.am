MAINTAINERCLEANFILES = Makefile.in
EXTRA_DIST =

bin_PROGRAMS = tempi
tempi_CXXFLAGS = #$(GSL_CFLAGS) $(HDF5_CFLAGS)
tempi_LDADD = #$(GSL_LIBS) $(HDF5_LIBS) #@CURSES_LIB@

noinst_HEADERS = \
  CommandLine.hh \
  Exception.hh \
  Representable.hh \
  StringVector.hh \
	OutputManipulator.hh \
	Validator.hh \
	Gpio.hh \
	Tty.hh \
	SerialLCD.hh \
	IPUtilities.hh

tempi_SOURCES = \
  CommandLine.cc \
  Representable.cc \
  StringVector.cc \
	Gpio.cc \
	Tty.cc \
	SerialLCD.cc \
	IPUtilities.cc \
	tempi.cc
