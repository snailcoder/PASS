#ifndef PRM_H_
#define PRM_H_

#include "Sampler.h"
#include "NearestNeighbors.h"
#include "LocalPlanner.h"
#include "GlobalPlanner.h"
#include "PlanningGraph.h"
#include "Solver.h"

// Probabilistic Roadmap, an effective planning algorithm in high-dimensional
// C-space, is simply implemented here. Usage sample:
// PRM prm(cspace, metric, sampler, nearest_neighbors, lp, gp, directed);
// prm.ConstructRoadmap(num);
// IntVector path = SolveQuery(start, goal);

// TODO(snailcoder@163.com): Add a disjoint set data member, according to 
// Probabilistic Roadmaps for Path Planning in High-Dimensional Configuration 
// Spaces, L.E. Kavraki, P. Svestka, J.-C. Latombe and M.H. Overmars, IEEE
// Trans. on Robotics and Automation, vol.12, No.4, 1996.
class PRM : public Solver {
 public:
  PRM(ConfigurationSpace *cspace, 
      Metric *metric, 
      Sampler *sp, 
      NearestNeighbors *nn, 
      LocalPlanner *lp, 
      GlobalPlanner *gp, 
      bool directed = false);
  void ConstructRoadmap(unsigned num);
  virtual IntVector SolveQuery(const RealCoord &start, 
                               const RealCoord &goal) const;
  PlanningGraph roadmap() const;
 private:
  PRM(const PRM &prm);
  PRM operator =(const PRM &prm);
  Sampler *sampler_;
  NearestNeighbors *neighbors_;
  LocalPlanner *lplanner_;
  GlobalPlanner *gplanner_;
  PlanningGraph roadmap_;
};

#endif