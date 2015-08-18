#ifndef CUBEROBOT_H_
#define CUBEROBOT_H_

#include "robot.h"

// CubeRobot is just a simple cube which is regarded as a robot
class CubeRobot : public Robot {
 public:
  CubeRobot();
  ~CubeRobot();
  virtual void TransformComponents();
 private:
  CubeRobot(const CubeRobot &robot);
  CubeRobot operator =(const CubeRobot &robot);
};

#endif