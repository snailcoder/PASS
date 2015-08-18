#include "robot.h"
#include "collisionmodel.h"

Robot::Robot(unsigned dof) : Object(dof) {
}
Robot::~Robot() {
}
bool Robot::ColDetWithObject(Object *obj) {
  std::vector<Model*> coms = obj->components();
  for (std::vector<Model*>::iterator iter1 = components_.begin();
	  iter1 != components_.end(); ++iter1) {
    for (std::vector<Model*>::iterator iter2 = coms.begin();
		iter2 != coms.end(); ++iter2) {
      CollisionModel model1(*iter1);
      CollisionModel model2(*iter2);
	  if (model1.Collision(model2)) {
        return true;
	  }
	}
  }
  return false;
}
bool Robot::ColDetWithSelf() {
  for (std::vector<Model*>::iterator iter1 = components_.begin();
	  iter1 != components_.end(); ++iter1) {
    for (std::vector<Model*>::iterator iter2 = iter1 + 1;
		iter2 != components_.end(); ++iter2) {
      CollisionModel model1(*iter1);
      CollisionModel model2(*iter2);
	  if (model1.Collision(model2)) {
        return true;
	  }
	}
  }
  return false;
}