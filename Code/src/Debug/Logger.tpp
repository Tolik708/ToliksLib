#ifndef LOGGER_TPP
#define LOGGER_TPP

namespace Tolik
{
template<typename T, typename... Args>
void Logger::Print(T &&t, Args&&... args) const
{
  std::cout << std::forward<T>(t);
  Print(args...);
}

template<std::size_t S, typename T, typename... Args>
void Logger::Iterate(std::array<std::string, S> &container, T &&t, Args&&... args) const
{
  s_stream << std::forward<T>(t);
  container[sizeof...(Args)] = s_stream.str();
  s_stream.str(std::string());
  Iterate<S>(container, args...);
}


template<typename... Args>
void Logger::LogMessage(const std::string &format, Args&&... args) const
{
  // We can't easily acces raw char array of string stream, so I decided to just save strings.
  std::array<std::string, sizeof...(Args)> convertedArguments;
  Iterate<sizeof...(Args)>(convertedArguments, args...);

  std::size_t lastPosition = 0;
  std::size_t atSignPosition = format.find('@', 0);

  if (atSignPosition == std::string::npos)
  {
    Print(format, args...);
    return;
  }

  while (atSignPosition != std::string::npos)
  {
    std::size_t numberLength = 0;
    while ((atSignPosition + numberLength + 1) != format.size() && isdigit(format[atSignPosition + numberLength + 1])) numberLength++;
    if (numberLength == 0)
    {
      atSignPosition = format.find('@', atSignPosition + 1);
      continue;
    }
    
    //we know that std::stoi won't fail because number length shows us that it is number
    std::size_t index = std::stoi(format.substr(atSignPosition + 1, numberLength));
    if (index < convertedArguments.size())
    {
      Print(std::string(&format[lastPosition], &format[atSignPosition]));
      Print(convertedArguments[index]);
      lastPosition = atSignPosition + numberLength + 1;
    }
    
    atSignPosition = format.find('@', atSignPosition + 1);
  }

  if(lastPosition < format.size())
    Print(std::string(&format[lastPosition], &format[format.size()]));
}
}

#endif