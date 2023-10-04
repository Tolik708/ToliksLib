#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <unordered_map>
#include <string>
#include <functional>
#include <sstream>
#include <vector>
#include <stdint.h>
#include <cassert>

namespace Tolik
{
class Debug;

enum class LogType : char
{
  Info = 0,
  Warning,
  Error
};

struct LoggerState
{
  LogType logType;
};

class Logger
{
  using PatternType = std::vector<std::pair<std::string, std::function<std::string(const LoggerState&)>>>;
public:
  Logger(const std::string &patternString);

  template<typename... Args> inline void Error  (const std::string &format, Args&&... args)
  { 
    state.logType = LogType::Error;   LogInfo(m_pattern); LogMessage(format, args...); LogInfo(m_postPattern);
    #ifdef DEBUG
    assert(false);
    #endif
  }
  template<typename... Args> inline void Warning(const std::string &format, Args&&... args)
  { state.logType = LogType::Warning; LogInfo(m_pattern); LogMessage(format, args...); LogInfo(m_postPattern); }
  template<typename... Args> inline void Info   (const std::string &format, Args&&... args)
  { state.logType = LogType::Info;    LogInfo(m_pattern); LogMessage(format, args...); LogInfo(m_postPattern); }

  template<typename... Args, typename T, std::enable_if_t<!std::is_convertible_v<T, std::string>, bool> = true> inline void Error  (T&& t, Args&&... args)
  { 
    state.logType = LogType::Error;   LogInfo(m_pattern); Print(t, args...); LogInfo(m_postPattern); 
    #ifdef DEBUG
    assert(false);
    #endif
  }
  template<typename... Args, typename T, std::enable_if_t<!std::is_convertible_v<T, std::string>, bool> = true> inline void Warning(T&& t, Args&&... args)
  { state.logType = LogType::Warning; LogInfo(m_pattern); Print(t, args...); LogInfo(m_postPattern); }
  template<typename... Args, typename T, std::enable_if_t<!std::is_convertible_v<T, std::string>, bool> = true> inline void Info   (T&& t, Args&&... args)
  { state.logType = LogType::Info;    LogInfo(m_pattern); Print(t, args...); LogInfo(m_postPattern); }

private:
  void LogInfo(const PatternType &patern) const;

  template<typename... Args> void LogMessage(const std::string &format, Args&&... args) const;
  template<std::size_t S, typename T, typename... Args> void Iterate(std::array<std::string, S> &container, T &&t, Args&&... args) const;
  template<std::size_t S> void inline Iterate(std::array<std::string, S> &container) const {}
 
  template<typename T, typename... Args> void Print(T &&t, Args&&... args) const;
  void Print() const {}

  PatternType m_pattern;
  PatternType m_postPattern;

  LoggerState state;

  static std::ostringstream s_stream;
  static const std::unordered_map<LogType, std::string> s_logTypeNameMap;
  static const std::unordered_map<LogType, uint32_t> s_logTypeColorMap;
  static const std::unordered_map<char, std::function<std::string(const LoggerState&)>> s_charFunctionMap;

  static std::string GetTimeString(const LoggerState &state);
  static std::string GetLogTypeName(const LoggerState &state) { return s_logTypeNameMap.at(state.logType); }
};
}

#include "Debug/Logger.tpp"

#endif