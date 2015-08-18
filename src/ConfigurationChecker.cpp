#include "ConfigurationChecker.h"

ConfigurationChecker::ConfigurationChecker(ConfigurationSpace *cspace)
  : cspace_(cspace) {
}
bool ConfigurationChecker::FreeConfiguration(const RealCoord &config) const {
  Scene *scene = cspace_->scene();
  scene->Configuration2World(config);
  return scene->CollisionFree();
}
ConfigurationSpace* ConfigurationChecker::cspace() const {
  return cspace_;
}