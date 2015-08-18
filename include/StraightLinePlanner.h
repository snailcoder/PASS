#ifndef STRAIGHTLINEPLANNER_H_
#define STRAIGHTLINEPLANNER_H_

#include "LocalPlanner.h"

// A kind of local planner which try to connect two configurations with a 
// straight line. Sample usage:
// StraightLinePlanner slp(res, checker, metric);
// if (!slp(begin, end)) {
//   std::cout << "can not connect given configurations." << std::endl;
// }
class StraightLinePlanner : public LocalPlanner {
 public:
  StraightLinePlanner(double resolution, 
                      ConfigurationChecker *checker = NULL, 
                      Metric *metric = NULL);
  virtual bool Plan(const RealCoord &begin, 
                    const RealCoord &end) const;
  virtual bool operator ()(const RealCoord &begin, 
                           const RealCoord &end) const;
 private:
  double resolution_;
};

#endif