#include "Input/UserInput.hpp"

#include <stdint.h>

#include "Math/Vector.hpp"
#include "Debug/Debug.hpp"
#include "Input/KeyID.hpp"
#include "Utilities/EnumFunctions.hpp"

namespace Tolik
{
void UserInput::Update()
{
  for(std::size_t i = 1; i < ToUnderlying(KeyID::Count); i++)
  {
    if(m_keys[i] == KeyState::Down)
      m_keys[i] = KeyState::Pressed;
    else if(m_keys[i] == KeyState::Up)
      m_keys[i] = KeyState::NONE;
  }
  for(std::size_t i = 1; i < ToUnderlying(MouseButtonID::Count); i++)
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