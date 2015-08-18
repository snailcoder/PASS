#ifndef KNEAREST_H_
#define KNEAREST_H_

#include "NearestNeighbors.h"

// Find the k nearest neighbors of a certain state. Sample usage:
// KNearest kn(k, metric);
// UIntVector neighbors = kn.Nearest(state, state_set);
class KNearest : public NearestNeighbors {
 public:
  KNearest(unsigned k, Metric *metric = NULL);
  virtual UIntVector Nearest(const RealCoord &state, 
                             const RealCoordVector &state_set) const;
 private:
  unsigned k_;
};

#endif