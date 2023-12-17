#include "Cursor.hpp"

#include "SDL2/SDL.h"
#include "stb_image.h"

#include "Debug/Debug.hpp"
#include "Utilities/EnumFunctions.hpp"
#include "Rendering/Window.hpp"

namespace Tolik
{
void Cursor::Update()
{
  if(IsLocked() && !IsHidden())
    Warp(m_window->GetSize() / 2);

  // Texture rendering

  if(!IsCustom())
    return;
}

void Cursor::Warp(int x, int y)
{
  SDL_WarpMouseInWindow(m_window->GetSDLWindow(), x, y);
}

void Cursor::SetState(CursorState state)
{
  m_state = state;
  SetLocked(static_cast<bool>(m_state & CursorState::Locked));
  SetGrabed(static_cast<bool>(m_state & CursorState::Grabed));
  SetHidden(static_cast<bool>(m_state & CursorState::Hidden));
}

void Cursor::Lock()
{
  m_state |= CursorState::Locked;

  if(IsHidden())
    SDL_CALL(SDL_SetRelativeMouseMode(SDL_TRUE));
}

void Cursor::Unlock()
{
  m_state ^= m_state & CursorState::Locked;

  if(IsHidden())
    SDL_CALL(SDL_SetRelativeMouseMode(SDL_FALSE));
}

void Cursor::Grab()
{
  m_state |= CursorState::Grabed;

  SDL_SetWindowGrab(m_window->GetSDLWindow(), SDL_TRUE);
}

void Cursor::Ungrab()
{
  m_state ^= m_state & CursorState::Grabed;

  SDL_SetWindowGrab(m_window->GetSDLWindow(), SDL_FALSE);
}

void Cursor::Hide()
{
  m_state |= CursorState::Hidden;

  if(IsLocked())
    SDL_CALL(SDL_SetRelativeMouseMode(SDL_TRUE));

  SDL_CALL(SDL_ShowCursor(SDL_DISABLE));
}

void Cursor::Show()
{
  m_state ^= m_state & CursorState::Hidden;

  if(IsLocked())
    SDL_CALL(SDL_SetRelativeMouseMode(SDL_FALSE));

  SDL_CALL(SDL_ShowCursor(SDL_ENABLE));
}

void Cursor::SetTexture(const std::string &path)
{
  m_state |= CursorState::Custom;
}

void Cursor::ClearTexture()
{
  m_state ^= m_state & CursorState::Custom;
}
}