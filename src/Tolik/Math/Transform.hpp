#ifndef TOLIK_TRANSFORM_HPP
#define TOLIK_TRANSFORM_HPP

#include "Tolik/Setup.hpp"

#include "glm/gtx/quaternion.hpp"
#include "glm/ext.hpp"

#include "Tolik/Math/Vector.hpp"

namespace Tolik
{
class Transform
{
public:
  Transform() {}
  Transform(Transform *parent) : m_parent(parent) {}
  Transform(const Vec3 &localPosition) : m_localPosition(localPosition) {}

  inline Transform *GetParent() const { return m_parent; }

  inline Vec3 GetPosition() const { return m_localPosition + GetParentPosition(); }
  inline const Vec3 &GetLocalPosition() const { return m_localPosition; }
  inline void SetPosition(const Vec3 &position) { m_localPosition = position - GetParentPosition(); }
  inline void SetLocalPosition(const Vec3 &localPosition) { m_localPosition = localPosition; }

  inline Vec3 Forward()  const { return GetRotation() * Vec3::forward(); }
  inline Vec3 Backward() const { return GetRotation() * Vec3::backward(); }
  inline Vec3 Up()       const { return GetRotation() * Vec3::up(); }
  inline Vec3 Down()     const { return GetRotation() * Vec3::down(); }
  inline Vec3 Right()    const { return GetRotation() * Vec3::right(); }
  inline Vec3 Left()     const { return GetRotation() * Vec3::left(); }

  inline Qua GetRotation() const { return GetParentRotation() * m_localRotation; }
  inline const Qua &GetLocalRotation() const { return m_localRotation; }
  inline void SetRotation(const Qua &rotation) { m_localRotation = rotation * GetParentRotation().Inversed(); }
  inline void SetLocalRotation(const Qua &localRotation) { m_localRotation = localRotation; }

  inline Vec3 GetScale() const { return m_localScale * GetParentScale(); }
  inline const Vec3 &GetLocalScale() const { return m_localScale; }
  inline void SetScale(const Vec3 &scale) { m_localScale = scale / GetParentScale(); }
  inline void SetLocalScale(const Vec3 &localScale) { m_localScale = localScale; }

  inline glm::mat4 GetWorldToLocalMatrix() const { return glm::translate(glm::mat4(1), GetPosition().ToGlm()) * glm::toMat4(GetRotation().ToGlm()) /* * glm::scale(glm::mat4(1), GetScale().ToGlm()) */; }

private:
  Transform *m_parent = nullptr;
  Vec3 m_localPosition = Vec3::zero();
  Vec3 m_localScale = Vec3::one();
  Qua m_localRotation = Qua::identity();

  inline Vec3 GetParentPosition() const { return m_parent == nullptr ? Vec3::zero() : m_parent->GetPosition(); }
  inline Vec3 GetParentScale() const { return m_parent == nullptr ? Vec3::zero() : m_parent->GetScale(); }
  inline Qua GetParentRotation() const { return m_parent == nullptr ? Qua::identity() : m_parent->GetRotation(); }
};
}

#endif