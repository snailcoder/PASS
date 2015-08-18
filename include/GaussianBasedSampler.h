#ifndef	GAUSSIANBASEDSAMPLER_H_
#define	GAUSSIANBASEDSAMPLER_H_

#include "Sampler.h"

// Base class of some samplers which generate samples subject to Gaussian 
// distribution. Famous Gaussian-Based-Sampler include Gaussian sampler 
// and Randomized Bridge Builder. They both need a Gaussian random number
// generator and a standard deviation.

class GaussianBasedSampler : public Sampler {
 public:
  GaussianBasedSampler(const RealCoord &stddev, 
                       Rng *rng, 
                       ConfigurationChecker *checker = NULL);
  void set_std(const RealCoord &stddev);
 protected:
  RealCoord stddev_;
};

#endif