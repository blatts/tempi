// -*- mode: C++ -*-
// Time-stamp: "2012-11-23 16:23:24 sb"

/*
  file       Owfs.hh
  copyright  (c) Sebastian Blatt 2012

 */


#ifndef OWFS_HH__9D07D4DB_6863_4245_8BD6_73A7DEEF8470
#define OWFS_HH__9D07D4DB_6863_4245_8BD6_73A7DEEF8470

#include <string>
#include <vector>
#include <map>

class DS18B20 {
  private:
    const std::string mount_point;
    const std::string owfs_id;
    const std::string name;

  public:
    DS18B20(const std::string& mount_point_,
            const std::string& owfs_id_,
            const std::string& name_);
    double ReadTemperature();
    const std::string& GetName() const {return name;}
};

class Owfs {
  private:
    const std::string mount_point;
    std::vector<DS18B20*> temperature_sensors;
  public:
    Owfs(const std::string& mount_point_);
    ~Owfs();
    void RegisterTemperatureSensor(const std::string& owfs_id,
                                   const std::string& name);
    void ReadTemperatures(std::map<std::string, double>& result);
};


#endif // OWFS_HH__9D07D4DB_6863_4245_8BD6_73A7DEEF8470

// Owfs.hh ends here
