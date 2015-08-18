#include "BridgeSampler.h"

BridgeSampler::BridgeSampler(const RealCoord &stddev, 
                             Rng *rng, 
                             ConfigurationChecker *checker)
  : GaussianBasedSampler(stddev, rng, checker) {
}
RealCoordVector BridgeSampler::Sample(unsigned num, 
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
  if (stddev_.dim() != dim) {
    throw std::out_of_range("Invalid standard deviation");
  }
  unsigned cnt = 0;
  while (cnt < num) {
    RealCoord c1(dim);
	for (unsigned i = 0; i < dim; ++i) {
      c1[i] = rng_->Uniform(lower[i], upper[i]);
	}
	if (!checker_->FreeConfiguration(c1)) {  // if c1 is in collision...
      RealCoord c2(dim);                     // generate a new configuration c2 
	                                         // according to Gaussian distribution.
	  for (unsigned j = 0; j < dim; ++j) {
        c2[j] = rng_->Gaussian(lower[j], upper[j], c1[j], stddev_[j]);
	  }
	  if (!checker_->FreeConfiguration(c2)) {  // if c2 is in collision...
        RealCoord mid = 0.5 * (c1 + c2);       // test the midpoint of c1 and c2.
		if (checker_->FreeConfiguration(mid)) {  // if midpoint is free...
          samples.push_back(mid);                // keep it as a milestone.
          ++cnt;
		}
	  }
	}
  }
  return samples;
}
RealCoordVector BridgeSampler::operator ()(unsigned num, 
                                           const RealCoord &lower, 
                                           const RealCoord &upper) const {
  return Sample(num, lower, upper);
}