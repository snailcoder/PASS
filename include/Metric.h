#ifndef METRIC_H_
#define METRIC_H_

#include "common.h"

// Compute the distance between two coordinates.
class Metric {
 public:
  virtual double Distance(const RealCoord &c1, 
                          const RealCoord &c2) const = 0 ;
  virtual double operator()(const RealCoord &c1, 
                            const RealCoord &c2) const = 0;
};
class Euclidean : public Metric {
 public:
  virtual double Distance(const RealCoord &c1, 
                          const RealCoord &c2) const;
  virtual double operator()(const RealCoord &c1, 
                            const RealCoord &c2) const;
};
class Manhattan : public Metric {
 public:
  virtual double Distance(const RealCoord &c1, 
                          const RealCoord &c2) const;
  virtual double operator()(const RealCoord &c1,
                            const RealCoord &c2) const;
};
class WeightedEuclidean : public Metric {
 public:
  WeightedEuclidean(const RealCoord &weights);
  virtual double Distance(const RealCoord &c1, 
                          const RealCoord &c2) const;
  virtual double operator()(const RealCoord &c1, 
                            const RealCoord &c2) const;
 private:
  RealCoord weights_;
};
class WeightedManhattan : public Metric {
 public:
  WeightedManhattan(const RealCoord &weights);
  virtual double Distance(const RealCoord &c1, 
                          const RealCoord &c2) const;
  virtual double operator()(const RealCoord &c1, 
                            const RealCoord &c2) const;
 private:
  RealCoord weights_;
};

#endif