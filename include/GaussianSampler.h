#ifndef GAUSSIANSAMPLER_H_
#define GAUSSIANsAMPLER_H_

#include "GaussianBasedSampler.h"

// Generate samples around obstacle boundry according to Gaussian distribution. 
// Sample usage:
// GaussianSampler sampler(stddev, rng, checker);
// RealCoordVector samples = sampler.Sample(num, lower, upper);
class GaussianSampler : public GaussianBasedSampler {
 public:
  GaussianSampler(const RealCoord &stddev,  // standard deviation
                  Rng *rng,   // random number generator
                  ConfigurationChecker *checker = NULL);
  virtual RealCoordVector Sample(unsigned num, 
                                 const RealCoord &lower, 
                                 const RealCoord &upper) const;
  virtual RealCoordVector operator ()(unsigned num, 
                                      const RealCoord &lower, 
                                      const RealCoord &upper) const;
};

#endif