#ifndef TOLIK_CAMERA_HPP
#define TOLIK_CAMERA_HPP

#include "Tolik/Setup.hpp"

#include "glm/ext.hpp"

#include "Tolik/Math/Transform.hpp"

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