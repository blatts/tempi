// -*- mode: C++ -*-
// Time-stamp: "2012-02-16 19:00:36 sb"

/*
  file       IPUtilities.cc
  copyright  (c) Sebastian Blatt 2012

 */

#include "IPUtilities.hh"
#include "Exception.hh"

#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <cstring>

#include <errno.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <ifaddrs.h>

std::string StringFromIPAddress(uint32_t address_in_host_byte_order) {
  struct in_addr in;
  in.s_addr = htonl(address_in_host_byte_order);
  return std::string(inet_ntoa(in));
}

uint32_t IPAddressFromString(const std::string& address){
  in_addr_t a;
  if((a = inet_addr(address.c_str())) == INADDR_NONE){
    std::ostringstream os;
    os << "inet_addr(" << address << ") failed\n"
       << strerror(errno) << "\n";
    throw EXCEPTION(os.str());
  }
  return (uint32_t)ntohl(a);
}

std::string GetLocalhostName(){
  int buflen = 0;
  if((buflen = sysconf(_SC_HOST_NAME_MAX)) == -1){
    std::ostringstream os;
    os << "sysconf(_SC_HOST_NAME_MAX) failed.\n"
       << strerror(errno) << "\n";
    throw EXCEPTION(os.str());
  }
  char* buf = (char*)malloc(sizeof(char)*buflen);
  if(gethostname(buf, buflen) == -1){
    std::ostringstream os;
    os << "gethostname() failed.\n"
       << strerror(errno) << "\n";
    free(buf);
    throw EXCEPTION(os.str());
  }
  std::string rc(buf);
  free(buf);
  return rc;
}

bool MatchSubnet(uint32_t address, uint32_t subnet, uint32_t netmask){
  return (address & netmask) == subnet;
}

uint32_t GetLocalhostIPAddress(uint32_t subnet, uint32_t netmask){
  struct ifaddrs* as;
  if(getifaddrs(&as)){
    std::ostringstream os;
    os << "getifaddrs() failed.\n"
       << strerror(errno) << "\n";
    throw EXCEPTION(os.str());
  }
  uint32_t address_host_order = 0;
  for(struct ifaddrs* a=as; a; a=a->ifa_next){
    if(a->ifa_addr->sa_family == AF_INET){
      struct sockaddr_in* b = (sockaddr_in*)a->ifa_addr;
      uint32_t c = ntohl(b->sin_addr.s_addr);
      //std::cout << StringFromIPAddress(c) << std::endl;
      if(MatchSubnet(c, subnet, netmask)){
        address_host_order = c;
        break;
      }
    }
  }
  freeifaddrs(as);

  if(address_host_order == 0){
    std::ostringstream os;
    os << "No IP address matches netmask "
       << StringFromIPAddress(subnet) << "/"
       << StringFromIPAddress(netmask);
    throw EXCEPTION(os.str());
  }
  return address_host_order;
}




// IPUtilities.cc ends here
