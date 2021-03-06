// -*- mode: C++ -*-
// Time-stamp: "2012-11-23 16:25:51 sb"

/*
  file       tempi.cc
  copyright  (c) Sebastian Blatt 2012

 */

#define PROGRAM_NAME         "tempi"
#define PROGRAM_DESCRIPTION  "Temperature logger on the Raspberry Pi"
#define PROGRAM_COPYRIGHT    "(C) Sebastian Blatt 2012"
#define PROGRAM_VERSION      "20121120"

#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>

#include "CommandLine.hh"
#include "Gpio.hh"
#include "SerialLCD.hh"
#include "IPUtilities.hh"
#include "Owfs.hh"
#include "OutputManipulator.hh"

static const char* program_options[] = {
  "Serial LCD tty device", "device", "d", "/dev/ttyAMA0"
  };

static const char* DS18B20_owfs_ids[] = {
  "28.07A92B040000", "T1",
  "28.23C22B040000", "T2",
  "28.2CB32B040000", "T3",
  "28.E23A2B040000", "T4",
  "28.E4FE2A040000", "T5"
  };


class LogScreen {
  private:
    const std::string& lcd_device;
    SerialLCD* p_lcd;
  public:
    LogScreen(const std::string& lcd_device_);
    ~LogScreen();

    void Clear();
    void MoveCursor(unsigned char position, unsigned char line = 0);
    void WriteString(const std::string& s);
};

LogScreen::LogScreen(const std::string& lcd_device_)
  : lcd_device(lcd_device_),
    p_lcd(NULL)
{
  try {
    p_lcd = new SerialLCD(lcd_device);
     Clear();
  }
  catch(const Exception& e){
    std::cerr << "Could not initialize Serial LCD port at \""
              << lcd_device << "\", will use stdout instead.\n"
              << "Are you sure I am running on a PI?"
              << std::endl;
    if(p_lcd){
      delete p_lcd;
      p_lcd = NULL;
    }
  }
}

LogScreen::~LogScreen(){
  if(p_lcd){
    delete p_lcd;
    p_lcd = NULL;
  }
}

void LogScreen::Clear(){
  if(p_lcd){
    p_lcd->Clear();
  }
}

void LogScreen::MoveCursor(unsigned char position, unsigned char line){
  if(p_lcd){
    p_lcd->MoveCursor(position, line);
  }
}

void LogScreen::WriteString(const std::string& s){
  if(p_lcd){
    p_lcd->WriteString(s);
  }
  else{
    std::cout << s << std::endl;
  }
}

std::string get_time(time_t t){
  struct tm* pt = localtime(&t);
  std::ostringstream os;
  os << std::setfill('0');
  os << std::setw(4) << pt->tm_year + 1900 << "-" 
     << std::setw(2) << pt->tm_mon + 1 << "-"
     << std::setw(2) << pt->tm_mday << " "
     << std::setw(2) << pt->tm_hour << ":"
     << std::setw(2) << pt->tm_min << ":"
     << std::setw(2) << pt->tm_sec;
  return os.str();
}
  


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

    const std::string device = cl.GetFlagData("-d");
    LogScreen lcd(device);
    lcd.Clear();
    lcd.MoveCursor(0, 0);
    lcd.WriteString("tempi started.");

    uint32_t subnet = IPAddressFromString("172.23.0.0");
    uint32_t netmask = IPAddressFromString("255.255.0.0");
    uint32_t ip_address = GetLocalhostIPAddress(subnet, netmask);
    std::ostringstream os;
    os << StringFromIPAddress(ip_address);
    std::cout << "IP address: " << os.str() << std::endl;

    lcd.MoveCursor(0, 1);
    lcd.WriteString(os.str());

    Owfs owfs("/mnt/onewire");
    for(size_t i=0; i<sizeof(DS18B20_owfs_ids)/sizeof(char*)/2; ++i){
      owfs.RegisterTemperatureSensor(DS18B20_owfs_ids[2*i], 
				     DS18B20_owfs_ids[2*i+1]);
    }

    
    std::ofstream of;
    of.open("data.txt");
    of << "unix_time" << "\t"
       << "date_string" << "\t";

    std::map<std::string, double> ts;
    bool first_run = true;
    while(true){
      owfs.ReadTemperatures(ts);
      if(first_run){
	first_run = false;
	for(std::map<std::string, double>::const_iterator i=ts.begin();
	    i != ts.end(); ++i){
	  of << i->first << "\t";
	}
	of << "\n";
      }

      lcd.MoveCursor(0, 0);
      std::ostringstream os;
      os << std::setiosflags(std::ios::fixed)
	 << std::setprecision(1)
	 << std::setfill('0')
	 << std::setw(4)
	 << ts["T1"] << " "
	 << std::setw(4)
	 << ts["T2"] << " "
	 << std::setw(4)
	 << ts["T3"] << " F";

      lcd.WriteString(os.str());

      time_t t = time(0);
      std::string time_s = get_time(t);
      of << (unsigned)t << "\t\"" << time_s << "\"\t";	
      for(std::map<std::string, double>::const_iterator i=ts.begin();
	  i != ts.end(); ++i)
      {
	of << i->second << "\t";
      }
      of << std::endl;
      sleep(3);
    }
  }
  catch(const Exception& e){
    std::cerr << e << std::endl;
    return 1;
  }

  return 0;
}

// tempi.cc ends here
