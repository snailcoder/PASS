#ifndef RNEAREST_H_
#define RNEAREST_H_

#include "NearestNeighbors.h"

// Find N nearest neighbors within the radius r. Sample usage:
// RNearest rn(r, neighbors, metric);
// UIntVector neighbors = rn.Nearest(state, state_set);
class RNearest : public NearestNeighbors {
 public:
  RNearest(double r, unsigned max_neighbors, Metric *metric = NULL);
  virtual UIntVector Nearest(const RealCoord &state, 
                             const RealCoordVector &state_set) const;
 private:
  double r_;
  unsigned max_neighbors_;
};

#endif