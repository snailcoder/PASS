#include <limits>
#include "KNearest.h"

KNearest::KNearest(unsigned k, Metric *metric)
  : NearestNeighbors(metric), k_(k) {
}
UIntVector KNearest::Nearest(const RealCoord &state, 
						     const RealCoordVector &state_set) const {
  UIntVector neighbors;
  std::size_t state_num = state_set.size();
  if (state_num <= k_) {
    for (unsigned i = 0; i < state_num; ++i) {
      neighbors.push_back(i);
    }
  } else {
    double *dist = new double[state_num];
	for (unsigned i = 0; i < state_num; ++i) {
      dist[i] = metric_->Distance(state, state_set[i]);
	}
	for (unsigned i = 0; i <= k_; ++i) {
      neighbors.push_back(i);
	}
	for (unsigned i = 1; i < k_; ++i) {
      double di = dist[i];
      unsigned j = i - 1;
	  while (j != std::numeric_limits<unsigned>::max() && dist[i] < dist[j]) {
        dist[j + 1] = dist[j];
        neighbors[j + 1] = neighbors[j];
        --j;
      }
      dist[j + 1] = di;
      neighbors[j + 1] = i;
    }
    for (unsigned i = k_; i < state_num; ++i) {
      double di = dist[i];
      unsigned j = k_ - 1;
	  while (j != std::numeric_limits<unsigned>::max() && dist[i] < dist[j]) {
        dist[j + 1] = dist[j];
        neighbors[j + 1] = neighbors[j];
        --j;
	  }
      neighbors[j + 1] = i;
	}
    delete[] dist;
  }
  neighbors.pop_back();
  return neighbors;
}