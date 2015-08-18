#ifndef BRIDGESAMPLER_H_
#define BRIDGESAMPLER_H_

#include "GaussianBasedSampler.h"

// Generate samples according to Randomized Bridge Builder(RBB). Sample usage:
// BridgeSampler sampler(stddev, rng, checker);
// RealCoordVector samples = sampler.Sample(num, lower, upper);
class BridgeSampler : public GaussianBasedSampler {
 public:
  BridgeSampler(const RealCoord &stddev, // standard deviation
                Rng *rng,  // random number generator
                ConfigurationChecker *checker = NULL);
  virtual RealCoordVector Sample(unsigned num, 
                                 const RealCoord &lower, 
                                 const RealCoord &upper) const;
  virtual RealCoordVector operator ()(unsigned num, 
                                      const RealCoord &lower, 
                                      const RealCoord &upper) const;
};

#endif