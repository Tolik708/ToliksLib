#include "Window.hpp"

#include <iostream>

#include "SDL2/SDL.h"

#include "Input/KeyID.hpp"
#include "Math/Vector.hpp"
#include "Debug/Debug.hpp"
#include "Rendering/Renderer.hpp"
#include "Rendering/OpenGL/RendererGL.hpp"
#include "Input/UserInput.hpp"

namespace Tolik
{
Window::~Window()
{
  SDL_DestroyWindow(m_window);
  SDL_Quit();
}

Window::Window(bool *running, UserInput *userInput)
  : m_running(running),
  m_userInput(userInput),
  m_renderer(new RendererGL()) // Here we decide what render API we will use
{
  SDL_CALL(SDL_Init(SDL_INIT_EVERYTHING) == 0);
  SDL_CALL(m_window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, m_renderer->GetSDLWindowFlags()));
  SDL_GetWindowSize(m_window, &m_width, &m_height);

  m_renderer->SetWindow(this);
}

void Window::ListenToEvents()
{
  m_userInput->Update();

  SDL_Event event;
  while(SDL_PollEvent(&event))
  {
    if(Debug::showSDLEvents)
      Debug::GetLogger().Info("SDL_Event: ", std::hex, event.type, std::dec);

    switch(event.type)
    {
    case SDL_QUIT:
      *m_running = false;
      break;
    case SDL_KEYDOWN:
      m_userInput->UpdateKeyDown(static_cast<uint16_t>(SDLScancodeToKeyID[event.key.keysym.scancode]));
      break;
    case SDL_KEYUP:
      m_userInput->UpdateKeyUp(static_cast<uint16_t>(SDLScancodeToKeyID[event.key.keysym.scancode]));
      break;
    case SDL_MOUSEBUTTONDOWN:
      m_userInput->UpdateMouseKeyDown(static_cast<uint16_t>(event.button.button));
      break;
    case SDL_MOUSEBUTTONUP:
      m_userInput->UpdateMouseKeyUp(static_cast<uint16_t>(event.button.button));
      break;
    case SDL_MOUSEWHEEL:
      m_userInput->UpdateMouseWheelDelta((m_userInput->GetKey(KeyID::LSHIFT) || m_userInput->GetKey(KeyID::RSHIFT)) ?
                                          Vec2(event.wheel.y, event.wheel.x) : Vec2(event.wheel.x, event.wheel.y));
      break;
    case SDL_MOUSEMOTION:
      m_userInput->UpdateMousePosition(Vec2(event.motion.x, event.motion.y), Vec2(event.motion.xrel, event.motion.yrel));
      break;
    case SDL_WINDOWEVENT:
      switch(event.window.type)
      {
        case SDL_WINDOWEVENT_RESIZED:
          SDL_GetWindowSize(m_window, &m_width, &m_height);
          m_renderer->UpdateDrawbleSize();
          break;
      }
      break;
    case SDL_TEXTINPUT:
      break;
    default:
      Debug::GetLogger("main").Warning("Unhandlet SDL_Event: @0", event.type);
      break;
    }
  }
}
}