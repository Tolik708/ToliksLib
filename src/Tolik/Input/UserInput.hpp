#ifndef TOLIK_USER_INPUT_HPP
#define TOLIK_USER_INPUT_HPP

#include <stdint.h>

#include "Tolik/Setup.hpp"

#include "Tolik/Math/Vector.hpp"
#include "Tolik/Utilities/EnumFunctions.hpp"
#include "Tolik/Input/KeyID.hpp"

namespace Tolik
{
class UserInput
{
public:
  void Update();

  inline void UpdateKeyDown(uint32_t key) { m_keys[key & 0xFFu] = KeyState::Down | (key & 0xFFFFFF00u); }
  inline void UpdateKeyUp(uint32_t key) { m_keys[key & 0xFFu] = KeyState::Up | (key & 0xFFFFFF00u); }
  inline void UpdateMouseKeyDown(uint8_t keyID) { m_mouseKeys[keyID] = KeyState::Down; }
  inline void UpdateMouseKeyUp(uint8_t keyID) { m_mouseKeys[keyID] = KeyState::Up; }
  inline void UpdateMousePosition(const Vec2 &mousePosition, const Vec2i &mouseDelta) { m_axises[ToUnderlying(InputAxis::MousePosition)] = mousePosition; m_axises[ToUnderlying(InputAxis::MouseDelta)] = mouseDelta; }
  inline void UpdateMouseWheelDelta(const Vec2 &mouseWheelDelta) { m_axises[ToUnderlying(InputAxis::MouseWheel)] = mouseWheelDelta; }

  inline bool GetKey(KeyID keyID) const     { return static_cast<bool>(m_keys[ToUnderlying(keyID & 0xFFu)]); }
  inline bool GetKeyDown(KeyID keyID) const { return static_cast<bool>(m_keys[ToUnderlying(keyID & 0xFFu)] & (KeyState::Down | (keyID & 0xFFFFFF00u))); }
  inline bool GetKeyUp(KeyID keyID) const   { return static_cast<bool>(m_keys[ToUnderlying(keyID & 0xFFu)] & (KeyState::Up   | (keyID & 0xFFFFFF00u))); }

  inline bool GetMouseKey(MouseButtonID mouseButtonID) const     { return m_mouseKeys[ToUnderlying(mouseButtonID)] == KeyState::Pressed; }
  inline bool GetMouseKeyDown(MouseButtonID mouseButtonID) const { return m_mouseKeys[ToUnderlying(mouseButtonID)] == KeyState::Down; }
  inline bool GetMouseKeyUp(MouseButtonID mouseButtonID) const   { return m_mouseKeys[ToUnderlying(mouseButtonID)] == KeyState::Up; }

  inline const Vec2 &GetAxis(InputAxis axis) const { return m_axises[ToUnderlying(axis)]; }

  inline const Vec2 &GetMousePosition() const { return m_axises[ToUnderlying(InputAxis::MousePosition)]; }
  inline const Vec2 &GetMouseDelta() const { return m_axises[ToUnderlying(InputAxis::MouseDelta)]; }
  inline const Vec2 &GetMouseWheel() const { return m_axises[ToUnderlying(InputAxis::MouseWheel)]; }

private:
  KeyState m_keys[KeyIDCount] = { KeyState::NONE };
  KeyState m_mouseKeys[MouseButtonIDCount] = { KeyState::NONE };
  Vec2 m_axises[InputAxisCount] = { Vec2::zero() };
};
}

#endif