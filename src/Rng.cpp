#include <cstdlib>
#include <cmath>
#include <stdexcept>
#include "Rng.h"

Rng::Rng(unsigned seed){
  srand(seed);
}
double Rng::Uniform(double lower, double upper) {
  if (lower > upper) {
    throw std::invalid_argument("Invalid sample range.");
  }
  return lower + (double)rand() / RAND_MAX * (upper - lower);
}
double Rng::Gaussian(double lower, double upper, 
                     double mean, double std) {
  if (lower > upper) {
    throw std::invalid_argument("Invalid sample range.");
  } 
  double d = MarsagliaPolar(mean, std);
  if (d < lower) {
    d = lower;
  } else if (d > upper) {
    d = upper;
  }
  return d;
}
double Rng::MarsagliaPolar(double mean, double std) {
  static bool has_spare = false;
  static double spare;
  if (has_spare) {
    has_spare = false;
    return mean + spare * std;
  }
  has_spare = true;
  static double u, v, s;
  do {
    u = (double)rand() / RAND_MAX * 2 - 1;
    v = (double)rand() / RAND_MAX * 2 - 1;
    s = u * u + v * v;
  } while (s >= 1 || s == 0);
  s = sqrt(-2.0 * log(s) / s);
  spare = v * s;
  return mean + u * s * std;
}