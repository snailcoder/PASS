#include "ConfigurationSpace.h"

ConfigurationSpace::ConfigurationSpace(Scene *scene)
  : scene_(scene), 
    dim_(0) {
  Init();
}
void ConfigurationSpace::Init() {
  std::vector<Robot*> robots = scene_->robots();
  for (std::vector<Robot*>::iterator iter = robots.begin();
	  iter != robots.end(); ++iter) {
    dim_ += (*iter)->dof();
  }
  RealCoord lower(dim_), upper(dim_);
  int offset = 0;
  for (std::vector<Robot*>::iterator iter = robots.begin();
	  iter != robots.end(); ++iter) {
    RealCoord lower_state = (*iter)->lower_state();
    RealCoord upper_state = (*iter)->upper_state();
    int dof = (*iter)->dof();
	for (int i = 0; i < dof; ++i) {
      lower[offset + i] = lower_state[i];
      upper[offset + i] = upper_state[i];
	}
    offset += dof;
  }
  lower_bound_ = lower;
  upper_bound_ = upper;
}
RealCoord ConfigurationSpace::lower_bound() const {
  return lower_bound_;
}
RealCoord ConfigurationSpace::upper_bound() const {
  return upper_bound_;
}
unsigned ConfigurationSpace::dim() const {
  return dim_;
}
Scene *ConfigurationSpace::scene() const {
  return scene_;
}