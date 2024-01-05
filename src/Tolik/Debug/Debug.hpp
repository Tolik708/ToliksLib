#ifndef TOLIK_DEBUG_HPP
#define TOLIK_DEBUG_HPP

#include <unordered_map>
#include <string>

#include "Tolik/Setup.hpp"

#include "glad/glad.h"


#include "Tolik/Debug/Logger.hpp"

#define SDL_CALL(command) \
  do { \
    if(::Detail::DebugSDLCheck(command)) \
      Debug::GetLogger("main").Error("\"@3\", command @2, file @0, line @1", __FILE__, __LINE__, #command, SDL_GetError()); \
  } while(0)
  
#define GL_CALL(command) do { \
    command; \
    while(uint32_t error = glGetError()) \
      Debug::GetLogger("main").Error("\"@3\", command @2, line @1, file @0", __FILE__, __LINE__, #command, Debug::GLErrorsNamesMap.at(error)); \
  } while(0)

namespace Detail
{
  template<typename T, std::enable_if_t<!std::is_pointer_v<T> && !std::is_arithmetic_v<T>, bool> = true> bool DebugSDLCheck(T t) { return false; }
  template<typename T, std::enable_if_t<std::is_pointer_v<T>, bool> = true> bool DebugSDLCheck(T t) { return t == nullptr; }
  template<typename T, std::enable_if_t<std::is_arithmetic_v<T>, bool> = true> bool DebugSDLCheck(T t) { return (t < 0); }
}

namespace Tolik
{
class Debug
{
public:
  Debug();
  static const Debug &Get() { return s_instance; }
  static Logger &GetLogger(const std::string &name = "main"); // Can't return const reference because of optimization
  static void AddLogger(const std::string &name, const Logger &logger);


  static const std::unordered_map<uint32_t, std::string> GLErrorsNamesMap;

  static const bool showSDLEvents;

private:
  std::unordered_map<std::string, Logger> m_loggers;
  
  static Debug s_instance;
};
}

#endif