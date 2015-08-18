#include <iostream>
#include <fstream>
#include "object.h"

Object::Object(unsigned dof)
  : dof_(dof),
    state_(dof),
    upper_state_(dof),
	lower_state_(dof) {
}
Object::~Object() {
}
unsigned Object::dof() const {
  return dof_;
}
std::vector<Model*> Object::components() const {
  return components_;
}
std::vector<Model*>::size_type Object::num_components() const {
  return components_.size();
}
RealCoord Object::state() const {
  return state_;
}
void Object::set_state(const RealCoord &state) {
  state_ = state;
  TransformComponents();
}
RealCoord Object::upper_state() const {
  return upper_state_;
}
RealCoord Object::lower_state() const {
  return lower_state_;
}
void Object::set_upper_state(const RealCoord &upper) {
  upper_state_ = upper;
}
void Object::set_lower_state(const RealCoord &lower) {
  lower_state_ = lower;
}
void Object::Clear() {
  for (std::vector<Model*>::iterator iter = components_.begin();
	  iter != components_.end(); ++iter) {
    if (*iter) {
      delete *iter;
    }
  }
  components_.clear();
}