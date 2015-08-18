#include "cubeobstacle.h"

CubeObstacle::CubeObstacle() : Obstacle(6) {
  Model *mod = new Model("data/cube.obj");
  try {
    mod->LoadBMPTexture("data/obmp.bmp");
    components_.push_back(mod);
  }
  catch(...) {
    delete mod;
    throw;
  }
}
CubeObstacle::~CubeObstacle() {
  Clear();
}
void CubeObstacle::TransformComponents() {
  components_[0]->TransformIdentity();
  components_[0]->rotate((float)state_[3], Vec3(1.0f, 0.0f, 0.0f));
  components_[0]->rotate((float)state_[4], Vec3(0.0f, 1.0f, 0.0f));
  components_[0]->rotate((float)state_[5], Vec3(0.0f, 0.0f, 1.0f));
  components_[0]->translate((float)state_[0], 
                            (float)state_[1], 
                            (float)state_[2]);
}