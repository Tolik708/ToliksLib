#ifndef USER_INPUT_HPP
#define USER_INPUT_HPP

#include <stdint.h>

#include "Math/Vector.hpp"
#include "Utilities/EnumFunctions.hpp"

namespace Tolik
{
enum class KeyID : uint16_t;
enum class MouseButtonID : uint8_t;

enum class InputAxis : unsigned char
{
  NONE=0,
  MouseWheel, MouseDelta, MousePosition,

  Count
};

enum class KeyState : uint8_t
{
  NONE=0, Pressed, Down, Up,

  Count
};

class UserInput
{
public:
  void Update();

  inline void UpdateKeyDown(uint16_t keyID) { m_keys[keyID] = KeyState::Down; }
  inline void UpdateKeyUp(uint16_t keyID) { m_keys[keyID] = KeyState::Up; }
  inline void UpdateMouseKeyDown(uint16_t keyID) { m_mouseKeys[keyID] = KeyState::Down; }
  inline void UpdateMouseKeyUp(uint16_t keyID) { m_mouseKeys[keyID] = KeyState::Up; }
  inline void UpdateMousePosition(const Vec2i &mousePosition, const Vec2i &mouseDelta) { m_axises[ToUnderlying(InputAxis::MousePosition)] = mousePosition; m_axises[ToUnderlying(InputAxis::MouseDelta)] = mouseDelta; }
  inline void UpdateMouseWheelDelta(const Vec2i &mouseWheelDelta) { m_axises[ToUnderlying(InputAxis::MouseWheel)] = mouseWheelDelta; }

  inline bool GetKey(KeyID keyID) const { return m_keys[ToUnderlying(keyID)] == KeyState::Pressed; }
  inline bool GetKeyDown(KeyID keyID) const { return m_keys[ToUnderlying(keyID)] == KeyState::Down; }
  inline bool GetKeyUp(KeyID keyID) const { return m_keys[ToUnderlying(keyID)] == KeyState::Up; }

  inline bool GetMouseKey(MouseButtonID mouseButtonID) const { return m_mouseKeys[ToUnderlying(mouseButtonID)] == KeyState::Pressed; }
  inline bool GetMouseKeyDown(MouseButtonID mouseButtonID) const { return m_mouseKeys[ToUnderlying(mouseButtonID)] == KeyState::Down; }
  inline bool GetMouseKeyUp(MouseButtonID mouseButtonID) const { return m_mouseKeys[ToUnderlying(mouseButtonID)] == KeyState::Up; }

  inline const Vec2i &GetAxis(InputAxis axis) const { return m_axises[ToUnderlying(axis)]; }
  inline const Vec2i &GetMousePosition() const { return m_axises[ToUnderlying(InputAxis::MousePosition)]; }
  inline const Vec2i &GetMouseDelta() const { return m_axises[ToUnderlying(InputAxis::MouseDelta)]; }
  inline const Vec2i &GetMouseWheel() const { return m_axises[ToUnderlying(InputAxis::MouseWheel)]; }

private:
  KeyState m_keys[512] = { KeyState::NONE };    // 0 - not used
  KeyState m_mouseKeys[4] = { KeyState::NONE }; // 0 - not used
  Vec2i m_axises[4] = { Vec2i::zero() };        // 0 - not used
};
}

#endif