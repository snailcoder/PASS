#ifndef COLLISIONMODEL_H_
#define COLLISIONMODEL_H_

#include "coldet/coldet.h"
#include "Model.h"

// Enclose model and collision model into a data structure,
// used in Robot class when implement ColDetWith* interface.

// TODO(snailcoder@163.com): Maybe this class is not necessary 
// if it's reasonable to put a CollisionModel3D data into Model class.
// Also, making it a nested class in Robot class is another choice...

class CollisionModel {
 public:
  CollisionModel(Model *model);
  ~CollisionModel();
  Model* model() const;
  CollisionModel3D *collision_model() const;
  bool Collision(CollisionModel &colmod);
 private:
  Model *model_;
  CollisionModel3D *collision_model_;
};

#endif