#ifndef CURSOR_HPP
#define CURSOR_HPP

#include <stdint.h>
#include <string>

#include "Math/Vector.hpp"
#include "Utilities/EnumFunctions.hpp"

namespace Tolik
{
class Window;

enum class CursorState : uint8_t
{
  NONE = 0,
  Custom = BIT(0),

  Locked = BIT(1),
  Grabed = BIT(2),
  Hidden = BIT(3),
};

/* TODO:
1. Custom texture (sprite class required)
2. Animated texture
*/

class Cursor
{
friend class Window;

public:
  Cursor(Window *window) : m_window(window) {}
  ~Cursor() { ClearTexture(); }

  void SetTexture(const std::string &path);
  void ClearTexture();

  const Vec2i &GetHotspotPosition() const { return m_hotspotPosition; }
  void SetCursorHotspot(int x, int y) { m_hotspotPosition.x() = x; m_hotspotPosition.y() = y; }
  void SetCursorHotspot(const Vec2i &position) { m_hotspotPosition = position; }

  const Vec2i &GetPosition() { return m_position; }
  void Warp(int x, int y);
  inline void Warp(const Vec2i &position) { Warp(position.x(), position.y()); }

  CursorState GetState() { return m_state; }
  bool IsCustom() { return static_cast<bool>(m_state & CursorState::Custom); }
  bool IsLocked() { return static_cast<bool>(m_state & CursorState::Locked); }
  bool IsGrabed() { return static_cast<bool>(m_state & CursorState::Grabed); }
  bool IsHidden() { return static_cast<bool>(m_state & CursorState::Hidden); }

  void SetState(CursorState state);
  void Lock();
  void Unlock();
  void Grab();
  void Ungrab();
  void Hide();
  void Show();
  inline void SetLocked(bool state) { state ? Lock() : Unlock(); }
  inline void SetGrabed(bool state) { state ? Grab() : Ungrab(); }
  inline void SetHidden(bool state) { state ? Hide() : Show(); }


private:
  void Update();

  Window *m_window;
  CursorState m_state;
  Vec2i m_position;
  Vec2i m_hotspotPosition;
};
}

#endif