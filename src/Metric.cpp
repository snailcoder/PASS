#include <cmath>
#include <cassert>
#include "metric.h"

double Euclidean::Distance(const RealCoord &c1, 
						   const RealCoord &c2) const {
  unsigned dim = c1.dim();
  assert(dim == c2.dim());
  double dist = 0.0;
  for (unsigned i = 0; i < dim; ++i) {
    dist += (c1[i] - c2[i]) * (c1[i] - c2[i]);
  }
  return sqrt(dist);
}
double Euclidean::operator ()(const RealCoord &c1, 
							  const RealCoord &c2) const {
  return Distance(c1, c2);
}
double Manhattan::Distance(const RealCoord &c1, 
						   const RealCoord &c2) const {
  unsigned dim = c1.dim();
  assert(dim == c2.dim());
  double dist = 0.0;
  for (unsigned i = 0; i < dim; ++i) {
    dist += fabs(c1[i] - c2[i]);
  }
  return dist;
}
double Manhattan::operator ()(const RealCoord &c1, 
							  const RealCoord &c2) const {
  return Distance(c1, c2);
}
WeightedEuclidean::WeightedEuclidean(const RealCoord &weights)
  : weights_(weights) {
}
double WeightedEuclidean::Distance(const RealCoord &c1, 
								   const RealCoord &c2) const {
  unsigned dim = weights_.dim();
  assert(dim == c1.dim() && dim == c2.dim());
  double dist = 0.0;
  for (unsigned i = 0; i < dim; ++i) {
    dist += weights_[i] * (c1[i] - c2[i]) * (c1[i] - c2[i]);
  }
  return sqrt(dist);
}
double WeightedEuclidean::operator ()(const RealCoord &c1,
									  const RealCoord &c2) const {
  return Distance(c1, c2);
}
WeightedManhattan::WeightedManhattan(const RealCoord &weights)
  : weights_(weights) {
}
double WeightedManhattan::Distance(const RealCoord &c1, 
								   const RealCoord &c2) const {
  unsigned dim = weights_.dim();
  assert(dim == c1.dim() && dim == c2.dim());
  double dist = 0.0;
  for (unsigned i = 0; i < dim; ++i) {
    dist += weights_[i] * fabs(c1[i] - c2[i]);
  }
  return dist;
}
double WeightedManhattan::operator ()(const RealCoord &c1, 
									  const RealCoord &c2) const {
  return Distance(c1, c2);
}