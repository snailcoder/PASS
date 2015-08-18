#include "scene.h"

Scene::Scene() : num_robot_(0), num_obstacle_(0) {
}
int Scene::num_robot() const {
  return num_robot_;
}
int Scene::num_obstacle() const {
  return num_obstacle_;
}
std::vector<Robot*> Scene::robots() const {
  return robots_;
}
std::vector<Obstacle*> Scene::obstacles() const {
  return obstacles_;
}
void Scene::AddRobot(Robot *robot) {
  robots_.push_back(robot);
}
void Scene::AddObstacle(Obstacle *obstacle) {
  obstacles_.push_back(obstacle);
}
void Scene::Configuration2World(const RealCoord &config) {
  unsigned dofs = 0;
  typedef std::vector<Robot*>::iterator Iterator;
  for (Iterator iter = robots_.begin(); iter != robots_.end(); ++iter) {
    dofs += (*iter)->dof();
  }
  if (dofs != config.dim()) {
	  throw std::invalid_argument("");
  }
  int offset = 0;
  for (Iterator iter = robots_.begin(); iter != robots_.end(); ++iter) {
    int dof = (*iter)->dof();
    RealCoord state(dof);
	for (int i = 0; i < dof; ++i) {
      state[i] = config[offset + i];
	}
    (*iter)->set_state(state);
    offset += dof;
  }
}
RealCoord Scene::World2Configuration() const {
  int dofs = 0;
  typedef std::vector<Robot*>::const_iterator ConstIterator;
  for (ConstIterator iter = robots_.begin(); iter != robots_.end(); ++iter) {
    dofs += (*iter)->dof();
  }
  RealCoord config(dofs);
  int offset = 0;
  for (ConstIterator iter = robots_.begin(); iter != robots_.end(); ++iter) {
    RealCoord state = (*iter)->state();
    unsigned dim = state.dim();
	for (unsigned i = 0; i < dim; ++i) {
      config[offset + i] = state[i];
	}
  }
  return config;
}
bool Scene::CollisionFree() const {
  typedef std::vector<Robot*>::const_iterator ConstIterator;
  for (ConstIterator iter = robots_.begin(); iter != robots_.end(); ++iter) {
    if ((*iter)->ColDetWithSelf()) {
      return false;
	}
	for (ConstIterator riter = iter + 1; riter != robots_.end(); ++riter) {
      if ((*iter)->ColDetWithObject(*riter)) {
        return false;
	  }
	}
	for (std::vector<Obstacle*>::const_iterator oiter = obstacles_.begin();
		oiter != obstacles_.end(); ++oiter) {
      if ((*iter)->ColDetWithObject(*oiter)) {
        return false;
	  }
	}
  }
  return true;
}