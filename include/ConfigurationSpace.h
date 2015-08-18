#ifndef CONFIGURATIONSPACE_H_
#define CONFIGURATIONSPACE_H_

#include "scene.h"

class ConfigurationSpace {
 public:
  ConfigurationSpace(Scene *scene);
  void Init();
  RealCoord upper_bound() const;
  RealCoord lower_bound() const;
  unsigned dim() const;
  Scene *scene() const;
 private:
  Scene* scene_;  // The world space
  RealCoord upper_bound_;  // Upper bound of the C-space
  RealCoord lower_bound_;  // Lower bound of the C-space
  unsigned dim_;  // Number of dimensions of the C-space
};

#endif