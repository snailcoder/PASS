#ifndef ROBOT_H_
#define ROBOT_H_

#include <vector>
#include "object.h"
#include "collisiondetect.h"

// The base class of all kinds of robots. It implements the methods inherited from
// CollisionDetect: ColDetWithObject and ColDetWithSelf.
class Robot : public Object, public CollisionDetect {
 public:
  Robot(unsigned dof);
  virtual ~Robot();
  virtual bool ColDetWithObject(Object *obj);
  virtual bool ColDetWithSelf();
};

#endif