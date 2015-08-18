#ifndef SAMPLER_H_
#define SAMPLER_H_

#include "common.h"
#include "ConfigurationChecker.h"
#include "Rng.h"

// The base class of all kinds of samplers, such as Uniform sampler, 
// Gaussian sampler and Randomized Bridge Builder(RBB).
class Sampler {
 public:
  Sampler(Rng *rng, ConfigurationChecker *checker = NULL);
  virtual ~Sampler();
  void set_checker(ConfigurationChecker *checker);
  virtual RealCoordVector Sample(unsigned num, 
                                 const RealCoord &lower, 
                                 const RealCoord &upper) const = 0;
  virtual RealCoordVector operator ()(unsigned num, 
                                      const RealCoord &lower, 
                                      const RealCoord &upper) const = 0; 
 protected:
  ConfigurationChecker *checker_;
  Rng *rng_;
};

#endif