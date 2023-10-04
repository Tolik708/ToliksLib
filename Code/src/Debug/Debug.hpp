#ifndef DEBUG_HPP
#define DEBUG_HPP

#include <unordered_map>
#include <string>

#include "glad/glad.h"

#include "Debug/Logger.hpp"

#define SDL_CALL(command) do { \
    if(!(command)) \
      Debug::GetLogger("main").Error("\"@3\" in @2, line: @1, file: @0", __FILE__, __LINE__, #command, SDL_GetError()); \
  } while(0)
  
#define GL_CALL(command) do { \
    command; \
    while(GLenum error = glGetError()) \
      Debug::GetLogger("main").Error("\"@3\" in command: @2, line: @1, file: @0", __FILE__, __LINE__, #command, Debug::GLErrorsNamesMap.at(error)); \
  } while(0)

namespace Tolik
{
class Debug
{
public:
  Debug();
  static const Debug &Get() { return s_instance; }
  static Logger &GetLogger(const std::string &name = "main"); // Can't return const reference because of optimization
  static void AddLogger(const std::string &name, const Logger &logger);


  static const std::unordered_map<GLenum, std::string> GLErrorsNamesMap;

  static const bool showSDLEvents;

private:
  std::unordered_map<std::string, Logger> m_loggers;
  
  static Debug s_instance;
};
}

#endif