#ifndef LOCALPLANNER_H_
#define LOCALPLANNER_H_

#include "ConfigurationChecker.h"
#include "Metric.h"

// if two configurations can be connected by a collision-free edge,
// return true, else return false.
class LocalPlanner {
 public:
  LocalPlanner(ConfigurationChecker *checker = NULL, Metric *metric = NULL);
  virtual ~LocalPlanner();
  virtual bool Plan(const RealCoord &begin, 
                    const RealCoord &end) const = 0;
  virtual bool operator ()(const RealCoord &begin, 
                           const RealCoord &end) const = 0;
  Metric *metric() const;
  void set_checker(ConfigurationChecker *checker);
  void set_metric(Metric *metric);
 protected:
  ConfigurationChecker *checker_;
  Metric *metric_;
};

#endif