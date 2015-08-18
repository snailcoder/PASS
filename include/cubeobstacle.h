#ifndef CUBEOBSTACLE_H_
#define CUBEOBSTACLE_H_

#include "obstacle.h"

// CubeObstacle is just a simple cube which is regarded as an obstacle
class CubeObstacle : public Obstacle {
 public:
  CubeObstacle();
  ~CubeObstacle();
  virtual void TransformComponents();
 private:
  CubeObstacle(const CubeObstacle &obs);
  CubeObstacle operator =(const CubeObstacle &obs);
};

#endif