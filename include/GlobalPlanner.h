#ifndef GLOBALPLANNER_H_
#define GLOBALPLANNER_H_

#include "common.h"
#include "PlanningGraph.h"

// Base class of global planners, such as A-star planner and Dijkstra planner

class GlobalPlanner {
 public:
  virtual ~GlobalPlanner();
  virtual IntVector Plan(int start, 
                         int goal, 
                         const PlanningGraph &graph) const = 0;
  virtual IntVector operator()(int start, 
                               int goal, 
                               const PlanningGraph &graph) const = 0;
};

#endif