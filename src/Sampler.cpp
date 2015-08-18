#include <cstdlib>
#include <ctime>
#include "Sampler.h"

//Sampler::Sampler(Rng *rng) : rng_(rng), checker_(NULL) {
//}
Sampler::Sampler(Rng *rng, ConfigurationChecker *checker)
  : checker_(checker), 
    rng_(rng) {
}
Sampler::~Sampler() {
}
void Sampler::set_checker(ConfigurationChecker *checker) {
  checker_ = checker;
}