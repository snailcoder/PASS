#ifndef DIJKSTRAPLANNER_H_
#define DIJKSTRAPLANNER_H_

#include "GlobalPlanner.h"

// Find a path using Dijkstra algorithm. Sample usage: 
// DijkstraPlanner planner;
// IntVector path = planner.Plan(start, end, planning_graph)
class DijkstraPlanner : public GlobalPlanner {
 public:
  virtual IntVector Plan(int start, 
                         int goal, 
                         const PlanningGraph &graph) const;
  virtual IntVector operator ()(int start, 
                                int goal, 
                                const PlanningGraph &graph) const;
};

#endif