#include <stdexcept>
#include "GaussianSampler.h"

//GaussianSampler::GaussianSampler(Rng *rng)
//  : GaussianBasedSampler(rng) {
//}
//GaussianSampler::GaussianSampler(Rng *rng, const RealCoord &stddev) 
//  : GaussianBasedSampler(rng, stddev) {
//}
GaussianSampler::GaussianSampler(const RealCoord &stddev, 
                                 Rng *rng, 
                                 ConfigurationChecker *checker)
  : GaussianBasedSampler(stddev, rng, checker) {
}
RealCoordVector GaussianSampler::Sample(unsigned num, 
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
    RealCoord c1(dim), c2(dim);
	for (unsigned i = 0; i < dim; ++i) {
      c1[i] = rng_->Uniform(lower[i], upper[i]);
	  c2[i] = rng_->Gaussian(lower[i], upper[i], c1[i], stddev_[i]);
	}
    // if c1 if collision-free and c2 is in collision, 
    // reserve c1 as a milestone.
	if (checker_->FreeConfiguration(c1)
        && !checker_->FreeConfiguration(c2)) {
      samples.push_back(c1);
      ++cnt;
    // if c2 if collision-free and c1 is in collision, 
    // reserve c2 as a milestone.
	} else if (!checker_->FreeConfiguration(c1) 
               && checker_->FreeConfiguration(c2)) {
      samples.push_back(c2);
      ++cnt;
	}
    // else ignore both c1 and c2.
  }
  return samples;
}
RealCoordVector GaussianSampler::operator ()(unsigned num, 
                                             const RealCoord &lower, 
											 const RealCoord &upper) const {
  return Sample(num, lower, upper);
}