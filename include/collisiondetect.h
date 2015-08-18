#ifndef COLLISIONDETECT_H_
#define COLLISIONDETECT_H_

#include "object.h"

// Detect collision between objects(robots, obstacles, etc.) in the scene.
class CollisionDetect {
 public:
  virtual bool ColDetWithObject(Object *obj) = 0;
  virtual bool ColDetWithSelf() = 0;
};

#endif