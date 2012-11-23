// -*- mode: C++ -*-
// Time-stamp: "2012-11-23 16:23:59 sb"

/*
  file       Owfs.cc
  copyright  (c) Sebastian Blatt 2012

 */

#include "Owfs.hh"

#include <iostream>
#include <fstream>
#include <cstdlib>

DS18B20::DS18B20(const std::string& mount_point_,
                 const std::string& owfs_id_,
                 const std::string& name_)
  : mount_point(mount_point_),
    owfs_id(owfs_id_),
    name(name_)
{}

double DS18B20::ReadTemperature(){
  std::string path = mount_point + "/" + owfs_id + "/temperature12";
  std::ifstream is(path.c_str());
  char buf[128];
  is.getline(buf, sizeof(buf)/sizeof(char));
  is.close();
  return atof(buf);
}

Owfs::Owfs(const std::string& mount_point_)
  : mount_point(mount_point_),
    temperature_sensors()
{}

Owfs::~Owfs(){
  for(size_t i=0; i<temperature_sensors.size(); ++i){
    delete temperature_sensors[i];
    temperature_sensors[i] = NULL;
  }
  temperature_sensors.clear();
}

void Owfs::RegisterTemperatureSensor(const std::string& owfs_id,
                                     const std::string& name){
  DS18B20* p = new DS18B20(mount_point, owfs_id, name);
  temperature_sensors.push_back(p);
}

void Owfs::ReadTemperatures(std::map<std::string, double>& result){
  result.clear();
  for(size_t i=0; i<temperature_sensors.size(); ++i){
    DS18B20* p = temperature_sensors[i];
    result[p->GetName()] = p->ReadTemperature();
  }
}




// Owfs.cc ends here
