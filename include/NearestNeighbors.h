#ifndef	NEARESTNEIGHBORS_H_
#define NEARESTNEIGHBORS_H_

#include <vector>
#include "common.h"
#include "Metric.h"

// The base class of KNearest and RNearest.
class NearestNeighbors {
 public:
  NearestNeighbors(Metric *metric = NULL);
  virtual ~NearestNeighbors();
  virtual UIntVector Nearest(const RealCoord &state, 
                             const RealCoordVector &state_set) const = 0;
  Metric* metric() const;
  void set_metric(Metric *metric);
 protected:
  Metric *metric_;
};

#endif