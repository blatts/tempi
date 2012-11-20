// -*- mode: C++ -*-
// Time-stamp: "2012-02-16 19:08:10 sb"

/*
  file       IPUtilities.hh
  copyright  (c) Sebastian Blatt 2012

 */


#ifndef IPUTILITIES_HH__215922F6_CEA4_4A1C_AB00_D7696EDECB8F
#define IPUTILITIES_HH__215922F6_CEA4_4A1C_AB00_D7696EDECB8F

#include <string>
#include <stdint.h>

#include "OutputManipulator.hh"

// Convert 32-bit number in host byte order to IPV4 address string
// representation.
std::string StringFromIPAddress(uint32_t address_in_host_byte_order);

// Convert IPV4 address string representation to 32-bit number in host
// byte order.
uint32_t IPAddressFromString(const std::string& address);

// Get string representation of localhost using gethostname(3)
std::string GetLocalhostName();

// Match IPV4 address with given subnet and netmask, all in host byte order
bool MatchSubnet(uint32_t address, uint32_t subnet, uint32_t netmask);

// Look through the list of IPV4 addresses returned by getifaddrs(3)
// and return the first one matching subnet and netmask.
uint32_t GetLocalhostIPAddress(uint32_t subnet, uint32_t netmask);



#endif // IPUTILITIES_HH__215922F6_CEA4_4A1C_AB00_D7696EDECB8F

// IPUtilities.hh ends here
