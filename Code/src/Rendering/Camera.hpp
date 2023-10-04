#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "glm/ext.hpp"

#include "Math/Transform.hpp"

namespace Tolik
{
class Camera
{
public:
  Camera() {}
  Camera(const Transform &newTransform) : transform(newTransform) {}

  glm::mat4 GetViewMatrix() const;

  Transform transform;
  float FOV = 60;
};
}

#endif