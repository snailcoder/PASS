#ifndef RNG_H_
#define RNG_H_

// Random number generator. 
class Rng {
 public:
  Rng(unsigned seed);
  double Uniform(double lower, double upper);
  double Gaussian(double lower, double upper, double mean, double std);
 private:
  // Marsaglia polar method is "a pseudo-random number sampling method for
  // generating a pair of independent standard normal random variables"(Wikipedia).
  double MarsagliaPolar(double mean, double std);
};

#endif