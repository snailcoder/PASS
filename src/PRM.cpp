#include "IndexPriorityQueue.h"
#include "PRM.h"

PRM::PRM(ConfigurationSpace *cspace, Metric *metric, 
         Sampler *sp, NearestNeighbors *nn, 
         LocalPlanner *lp, GlobalPlanner *gp, bool directed)
  : Solver(cspace, metric), 
    sampler_(sp),  
    neighbors_(nn), 
    lplanner_(lp), 
    gplanner_(gp), 
    roadmap_(directed) {
  neighbors_->set_metric(metric_);
  lplanner_->set_metric(metric_);
}
void PRM::ConstructRoadmap(unsigned num) {
  ConfigurationChecker checker(cspace_);
  sampler_->set_checker(&checker);
  lplanner_->set_checker(&checker);
  RealCoord lower(cspace_->lower_bound());
  RealCoord upper(cspace_->upper_bound());
  // Generate samples in the C-space
  RealCoordVector samples = sampler_->Sample(num, lower, upper);
  // Add samples into the roadmap
  roadmap_.AddVertex(samples);
  RealCoordVector::size_type size = samples.size();
  // Traverse all samples, connect a sample with its nearest neighbors if
  // there is a collision-free edge between them.
  for (RealCoordVector::size_type i = 0; i < size; ++i) {
    UIntVector nns = neighbors_->Nearest(samples[i], samples);
    for (UIntVector::iterator niter = nns.begin(); 
        niter != nns.end(); ++niter) {
      if (i == *niter) {
        continue;
	  }
      if (!roadmap_.Edge(i, *niter) 
          && lplanner_->Plan(samples[i], samples[*niter])) {
        double weight = metric_->Distance(samples[i], samples[*niter]);
        roadmap_.AddEdge(i, *niter, weight);
	  }
    }
	std::cout << "processing sample: " << i << std::endl;
  }
}
IntVector PRM::SolveQuery(const RealCoord &start, 
                          const RealCoord &goal) const {
  IntVector path;
  int sid, gid;
  ConfigurationChecker checker(cspace_);
  lplanner_->set_checker(&checker);
  PlanningGraph query_graph(roadmap_);
  RealCoordVector samples = roadmap_.ExtractStates();
  // Try to connect the start configuration to its nearest neighbors.
  UIntVector nns = neighbors_->Nearest(start, samples);
  bool can_connect = false;
  for (UIntVector::iterator iter = nns.begin(); 
	  iter != nns.end(); ++iter) {
    if (lplanner_->Plan(start, samples[*iter])) {
      sid = query_graph.AddVertex(start);
      double dist = metric_->Distance(start, samples[*iter]);
      query_graph.AddEdge(sid, *iter, dist);
      can_connect = true;
      break;
	}
  }
  if (!can_connect) {
    return path;
  }
  // Try to connect the goal configuration to its nearest neighbors.
  UIntVector nng = neighbors_->Nearest(goal, samples);
  can_connect = false;
  for (UIntVector::iterator iter = nng.begin();
	  iter != nng.end(); ++iter) {
    if (lplanner_->Plan(goal, samples[*iter])) {
      gid = query_graph.AddVertex(goal);
      double dist = metric_->Distance(goal, samples[*iter]);
      query_graph.AddEdge(gid, *iter, dist);
      can_connect = true;
      break;
	}
  }
  if (!can_connect) {
    return path;
  }
  // Search a collision-free path.
  path = gplanner_->Plan(sid, gid, query_graph);
  return path;
}
PlanningGraph PRM::roadmap() const {
  return roadmap_;
}