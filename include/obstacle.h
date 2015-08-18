#ifndef OBSTACLE_H_
#define OBSTACLE_H_

#include <vector>
#include "object.h"

// The base class of all kinds of obstacles. Robot and obstacle are two 
// relative concepts. I cann't even distinguish them very clearly but I'm 
// sure they are different.
class Obstacle : public Object {
 public:
  Obstacle(unsigned dof);
  virtual ~Obstacle();
};

#endif