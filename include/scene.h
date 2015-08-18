#ifndef SCENE_H_
#define SCENE_H_

#include <vector>
#include "common.h"
#include "robot.h"
#include "obstacle.h"

// Robots and obstacles, maybe also other objects, are all in a certain scene.
// Actually, the scene is exactly the world space.
class Scene {
 public:
  Scene();
  int num_robot() const;
  int num_obstacle() const;
  std::vector<Robot*> robots() const;
  std::vector<Obstacle*> obstacles() const;
  void AddRobot(Robot *robot);
  void AddObstacle(Obstacle *obstacle);
  // Set states of objects in the scene according to the configuration.
  void Configuration2World(const RealCoord &config);
  // Conbine states of all robots to form a configuration.
  RealCoord World2Configuration() const;
  // Check if the scene is collision free right now.
  bool CollisionFree() const;
 private:
  int num_robot_;
  int num_obstacle_;
  std::vector<Robot*> robots_;
  std::vector<Obstacle*> obstacles_;
};

#endif