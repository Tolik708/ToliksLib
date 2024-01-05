#include "Tolik/Input/UserInput.hpp"

#include <stdint.h>

#include "Tolik/Math/Vector.hpp"
#include "Tolik/Input/KeyID.hpp"
#include "Tolik/Utilities/EnumFunctions.hpp"

namespace Tolik
{
void UserInput::Update()
{
  for(std::size_t i = 1; i < KeyIDCount; i++)
  {
    if(static_cast<bool>(m_keys[i] & KeyState::Down))
      m_keys[i] = KeyState::Pressed;
    else if(static_cast<bool>(m_keys[i] & KeyState::Up))
      m_keys[i] = KeyState::NONE;
  }
  for(std::size_t i = 1; i < MouseButtonIDCount; i++)
  {
    if(m_mouseKeys[i] == KeyState::Down)
      m_mouseKeys[i] = KeyState::Pressed;
    else if(m_mouseKeys[i] == KeyState::Up)
      m_mouseKeys[i] = KeyState::NONE;
  }

  m_axises[ToUnderlying(InputAxis::MouseDelta)] = Vec2i::zero();
  m_axises[ToUnderlying(InputAxis::MouseWheel)] = Vec2i::zero();
}
}