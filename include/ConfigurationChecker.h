#ifndef CONFIGURATIONCHECKER_H_
#define CONFIGURATIONCHECKER_H_

#include "common.h"
#include "ConfigurationSpace.h"

class ConfigurationChecker {
 public:
  ConfigurationChecker(ConfigurationSpace *cspace);
  // If the configuration is collision free, return true; else return false
  bool FreeConfiguration(const RealCoord &config) const;
  ConfigurationSpace *cspace() const;
 private:
  // Each checker should be bound to a certain C-space
  ConfigurationSpace *cspace_;  
};

#endif