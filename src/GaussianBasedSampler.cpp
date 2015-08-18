#include "GaussianBasedSampler.h"

//GaussianBasedSampler::GaussianBasedSampler(Rng *rng) : Sampler(rng) {
//}
//GaussianBasedSampler::GaussianBasedSampler(Rng *rng, const RealCoord &stddev)
//  : Sampler(rng), stddev_(stddev) {
//}
GaussianBasedSampler::GaussianBasedSampler(const RealCoord &stddev, 
                                           Rng *rng, 
                                           ConfigurationChecker *checker)
  : Sampler(rng, checker), stddev_(stddev) {
  if (stddev.dim() != checker->cspace()->dim()) {
    throw std::invalid_argument("Invalid stddev dimension.");
  }
}
void GaussianBasedSampler::set_std(const RealCoord &stddev) {
  stddev_ = stddev;
}