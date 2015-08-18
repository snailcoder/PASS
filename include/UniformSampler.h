#ifndef UNIFORMSAMPLER_H_
#define UNIFORMSAMPLER_H_

#include "Sampler.h"

// Generate a given number of samples according to uniform distribution.
// This is the simplest sample-generating method used in basic PRM.
class UniformSampler : public Sampler {
 public:
  UniformSampler(Rng *rng, ConfigurationChecker *checker = NULL);
  virtual RealCoordVector Sample(unsigned num, 
                                 const RealCoord &lower, 
                                 const RealCoord &upper) const;
  virtual RealCoordVector operator ()(unsigned num, 
                                      const RealCoord &lower, 
                                      const RealCoord &upper) const;
};

#endif