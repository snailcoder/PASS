#include "RNearest.h"

RNearest::RNearest(double r, unsigned max_neighbors, Metric *metric)
  : NearestNeighbors(metric), r_(r), max_neighbors_(max_neighbors) {
}
UIntVector RNearest::Nearest(const RealCoord &state, 
							 const RealCoordVector &state_set) const {
  UIntVector neighbors;
  std::size_t state_num = state_set.size();
  unsigned cnt = 0;
  for (unsigned i = 0; i < state_num && cnt < max_neighbors_; ++i) {
    if (metric_->Distance(state, state_set[i]) < r_) {
      neighbors.push_back(i);
      ++cnt;
	}
  }
  return neighbors;
}