#ifndef OBJECT_H_
#define OBJECT_H_

#include <vector>
#include <string>
#include "common.h"
#include "model.h"

// An object is a real entity in the scene, for example, an object could be
// an obstacle or a robot. It consist of some Models. An object should has 
// its own degree of freedom, configuration and so on.
class Object {
 public:
  Object(unsigned dof);
  virtual ~Object();
  unsigned dof() const;
  std::vector<Model*> components() const;
  std::vector<Model*>::size_type num_components() const;
  RealCoord state() const;
  void set_state(const RealCoord &state);
  RealCoord upper_state() const;
  RealCoord lower_state() const;
  void set_upper_state(const RealCoord &upper);
  void set_lower_state(const RealCoord &lower);
  void Clear();
  // Object transformation is reflected by model components transformation.
  virtual void TransformComponents() = 0;
 protected:
  unsigned dof_;   // Degree of freedom
  std::vector<Model*> components_;
  RealCoord state_;
  RealCoord upper_state_;
  RealCoord lower_state_;
};

#endif