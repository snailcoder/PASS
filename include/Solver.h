#ifndef SOLVER_H_
#define SOLVER_H_

#include "Metric.h"
#include "ConfigurationSpace.h"
#include "PlanningGraph.h"

// The base class of planning algorithms, such as PRM, DRM...
class Solver {
 public:
  Solver(ConfigurationSpace *cspace = NULL, Metric *metric = NULL);
  void set_metric(Metric *metric);
  void set_cspace(ConfigurationSpace *cspace);
  // Search a collision-free path from start to goal in the C-space.
  virtual IntVector SolveQuery(const RealCoord &start, 
                               const RealCoord &goal) const = 0;
 protected:
  ConfigurationSpace *cspace_;
  Metric *metric_;
};

#endif