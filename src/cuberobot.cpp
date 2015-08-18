#include "cuberobot.h"

CubeRobot::CubeRobot() : Robot(6) {
  Model *mod = new Model("data/cube.obj");
  try {
    mod->LoadBMPTexture("data/rbmp.bmp");
    components_.push_back(mod);
  }
  catch(...) {
    delete mod;
    throw;
  }
}
CubeRobot::~CubeRobot() {
  Clear();
}
void CubeRobot::TransformComponents() {
  components_[0]->TransformIdentity();
  components_[0]->rotate((float)state_[3], Vec3(1.0f, 0.0f, 0.0f));
  components_[0]->rotate((float)state_[4], Vec3(0.0f, 1.0f, 0.0f));
  components_[0]->rotate((float)state_[5], Vec3(0.0f, 0.0f, 1.0f));
  components_[0]->translate((float)state_[0], 
                            (float)state_[1], 
                            (float)state_[2]);
}