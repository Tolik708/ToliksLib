#ifndef TOLIK_RAY_HPP
#define TOLIK_RAY_HPP

#include "Setup.hpp"

#include "Tolik/Math/Vector.hpp"

namespace Tolik
{
class Ray
{
public:
  Ray(const Vec3 &newOrigin, const Vec3 &newDirection) : origin(newOrigin), direction(newDirection) {}

  inline Vec3 Calculate(float t) const { return origin + (direction * t); }

  Vec3 origin;
  Vec3 direction;
};
}

#endif    