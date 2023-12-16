#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "Rendering/Renderer.hpp"

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
  inline SDL_Window *GetWindow() const { return m_window; }
  inline const Renderer &GetRenderer() const { return m_renderer; }
  inline int GetWidth() const { return m_width; }
  inline int GetHeight() const { return m_height; }
  void LockCursor(bool state) const;
  void HideCursor(bool state) const;

private:
  Renderer m_renderer;
  bool *m_running;
  UserInput *m_userInput;
  SDL_Window *m_window;
  int m_width, m_height;
};
}

#endif