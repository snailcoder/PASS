#ifndef ASTRAPLANNER_H_
#define ASTARPLANNER_H_

#include "GlobalPlanner.h"

// Find a path using A-star algorithm. Sample usage: 
// AStarPlanner planner(heuristic);
// IntVector path = planner.Plan(start, end, planning_graph)
class AStarPlanner : public GlobalPlanner {
 public:
  AStarPlanner(Metric *heuristic = NULL);
  virtual IntVector Plan(int start, 
                         int goal, 
                         const PlanningGraph &graph) const;
  virtual IntVector operator()(int start, 
                               int goal, 
                               const PlanningGraph &graph) const;
  double Heuristic(int u, int v, const PlanningGraph &graph) const;
  void set_heuristic(Metric *heuristic);
 private:
  Metric *heuristic_;
};

#endif