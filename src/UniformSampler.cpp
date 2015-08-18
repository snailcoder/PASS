#include <cstdlib>
#include <stdexcept>
#include <iostream>
#include "UniformSampler.h"

UniformSampler::UniformSampler(Rng *rng, ConfigurationChecker *checker)
  : Sampler(rng, checker) {
}
RealCoordVector UniformSampler::Sample(unsigned num, 
                                       const RealCoord &lower, 
                                       const RealCoord &upper) const {
  RealCoordVector samples;
  if (!checker_ || !rng_) {
    return samples;
  }
  unsigned dim = checker_->cspace()->dim();
  if (lower.dim() != dim || upper.dim() != dim) {
    throw std::invalid_argument("Invalid sample range.");
  }
  unsigned cnt = 0;
  while (cnt < num) {
    RealCoord c(dim);
	for (unsigned i = 0; i < dim; ++i) {
      c[i] = rng_->Uniform(lower[i], upper[i]);
	}
	if (checker_->FreeConfiguration(c)) {
      samples.push_back(c);
      ++cnt;
	}
  }
  return samples;
}
RealCoordVector UniformSampler::operator ()(unsigned num, 
                                            const RealCoord &lower, 
                                            const RealCoord &upper) const {
  return Sample(num, lower, upper);
}