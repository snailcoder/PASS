#ifndef COMMON_H_
#define COMMON_H_

#include <vector>
#include "glm/glm.hpp"
#include "Coordinate.h"

typedef glm::vec2 Vec2;
typedef glm::vec3 Vec3;
typedef glm::mat4 Mat4;
typedef std::vector<glm::vec2> Vec2Vector;
typedef std::vector<glm::vec3> Vec3Vector;
typedef std::vector<glm::mat4> Mat4Vector;
typedef std::vector<int> IntVector;
typedef std::vector<unsigned int> UIntVector;
typedef std::vector<double> RealVector;
typedef Coordinate<double> RealCoord;
typedef std::vector<RealCoord> RealCoordVector;

#endif