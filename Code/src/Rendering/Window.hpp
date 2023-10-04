#ifndef WINDOW_HPP
#define WINDOW_HPP

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
  inline SDL_Window *GetWindow() { return m_window; }
  inline Renderer *GetRenderer() { return m_renderer; }
  inline int GetWidth() { return m_width; }
  inline int GetHeight() { return m_height; }

private:
  bool *m_running;
  UserInput *m_userInput;
  SDL_Window *m_window;
  Renderer *m_renderer;
  int m_width, m_height;
};
}

#endif