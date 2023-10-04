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

  inline void UpdateKeyDown(uint16_t keyID)
  { m_keys[keyID] = KeyState::Down; }
  inline void UpdateKeyUp(uint16_t keyID)
  { m_keys[keyID] = KeyState::Up; }
  inline void UpdateMouseKeyDown(uint16_t keyID)
  { m_mouseKeys[keyID] = KeyState::Down; }
  inline void UpdateMouseKeyUp(uint16_t keyID)
  { m_mouseKeys[keyID] = KeyState::Up; }
  inline void UpdateMousePosition(const Vec2 &mousePosition, const Vec2 &newMouseDelta)
  { m_axises[ToUnderlying(InputAxis::MousePosition)] = mousePosition; m_axises[ToUnderlying(InputAxis::MouseDelta)] = newMouseDelta; }
  inline void UpdateMouseWheelDelta(const Vec2 &newMouseWheelDelta)
  { m_axises[ToUnderlying(InputAxis::MouseWheel)] = newMouseWheelDelta; }

  inline bool GetKey(KeyID keyID) const
  { return (m_keys[static_cast<std::size_t>(keyID)] == KeyState::Pressed) || (m_keys[static_cast<std::size_t>(keyID)] == KeyState::Down); }
  inline bool GetKeyDown(KeyID keyID) const
  { return m_keys[static_cast<std::size_t>(keyID)] == KeyState::Down; }
  inline bool GetKeyUp(KeyID keyID) const
  { return m_keys[static_cast<std::size_t>(keyID)] == KeyState::Up; }

  inline bool GetMouseKey(MouseButtonID mouseButtonID) const
  { return (m_mouseKeys[static_cast<std::size_t>(mouseButtonID)] == KeyState::Pressed) || (m_mouseKeys[static_cast<std::size_t>(mouseButtonID)] == KeyState::Down); }
  inline bool GetMouseKeyDown(MouseButtonID mouseButtonID) const
  { return m_mouseKeys[static_cast<std::size_t>(mouseButtonID)] == KeyState::Down; }
  inline bool GetMouseKeyUp(MouseButtonID mouseButtonID) const
  { return m_mouseKeys[static_cast<std::size_t>(mouseButtonID)] == KeyState::Up; }

  inline const Vec2 &GetAxis(InputAxis type) const
  { return m_axises[ToUnderlying(type)]; }

private:
  KeyState m_keys[512] = { KeyState::NONE };    // 0 - not used
  KeyState m_mouseKeys[4] = { KeyState::NONE }; // 0 - not used
  Vec2 m_axises[4];        // 0 - not used
};
}

#endif