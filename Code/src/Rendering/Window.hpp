#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "Rendering/Renderer.hpp"
#include "Rendering/Cursor.hpp"
#include "Math/Vector.hpp"

class SDL_Window;

namespace Tolik
{
class UserInput;
class Renderer;

class Window
{
public:
  Window(bool *running, UserInput *userInput);
  ~Window();

  void ListenToEvents();
  inline SDL_Window *GetSDLWindow() const { return m_window; }
  inline Renderer &GetRenderer() { return m_renderer; }
  inline Cursor &GetCursor() { return m_cursor; }
  inline int GetWidth() const { return m_width; }
  inline int GetHeight() const { return m_height; }
  inline Vec2i GetSize() const { return Vec2i(m_width, m_height); }


private:
  Renderer m_renderer;
  bool *m_running;
  UserInput *m_userInput;
  SDL_Window *m_window;
  int m_width, m_height;
  Cursor m_cursor;
};
}

#endif