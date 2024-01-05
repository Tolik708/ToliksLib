#include "Tolik/Debug/Logger.hpp"

#include <unordered_map>
#include <string>
#include <functional>
#include <sstream>
#include <vector>
#include <stdint.h>
#include <ctime>
#include <iomanip>

#include "Tolik/Setup.hpp"

#include "Tolik/Debug/Debug.hpp"

namespace Tolik
{
const std::unordered_map<LogType, std::string> Logger::s_logTypeNameMap = 
{
  { LogType::Info,    "INFO" },
  { LogType::Warning, "WARNING" },
  { LogType::Error,   "ERROR" }
};

const std::unordered_map<LogType, uint32_t> Logger::s_logTypeColorMap = 
{
  { LogType::Info,    8 },
  { LogType::Warning, 14 },
  { LogType::Error,   12 }
};

const std::unordered_map<char, std::function<std::string(const LoggerState&)>> Logger::s_charFunctionMap =
{
	{ 'T', GetTimeString },
	{ 'S', GetLogTypeName }
};

std::ostringstream Logger::s_stream = std::ostringstream();

Logger::Logger(const std::string &patternString)
{
  PatternType *currentPattern = &m_pattern;
	std::size_t patternIndex = 0;
	std::size_t lastPosition = 0;
	std::size_t atSignPosition = patternString.find('@');

	currentPattern->emplace_back();

	while(atSignPosition != std::string::npos)
	{
		if(atSignPosition + 1 == patternString.size())
			break;

		switch(patternString[atSignPosition + 1])
		{
			case 'M':
				(*currentPattern)[patternIndex].first = std::string(&patternString[lastPosition], &patternString[atSignPosition]);
				currentPattern = &m_postPattern;
				lastPosition = atSignPosition + 2;
				currentPattern->emplace_back();
				patternIndex = 0;
				break;
			case 'T':
				(*currentPattern)[patternIndex].first = std::string(&patternString[lastPosition], &patternString[atSignPosition]);
				(*currentPattern)[patternIndex].second = GetTimeString;
				lastPosition = atSignPosition + 2;
				currentPattern->emplace_back();
				patternIndex++;
				break;
			case 'S':
				(*currentPattern)[patternIndex].first = std::string(&patternString[lastPosition], &patternString[atSignPosition]);
				(*currentPattern)[patternIndex].second = GetLogTypeName;
				lastPosition = atSignPosition + 2;
				currentPattern->emplace_back();
				patternIndex++;
				break;
			default:
				break;
		}

		atSignPosition = patternString.find('@', atSignPosition + 1);
	}

	(*currentPattern)[patternIndex].first = std::string(&patternString[lastPosition], &patternString[patternString.size()]);
}

void Logger::LogInfo(const PatternType &pattern) const
{
	for (std::size_t i = 0; i < pattern.size(); i++)
	{
		Print(pattern[i].first);
		if (pattern[i].second != nullptr)
			Print(pattern[i].second(state));
	}
}

std::string Logger::GetTimeString(const LoggerState &state)
{
	std::time_t seconds = time(NULL);
	std::tm *buf = localtime(&seconds);
	return std::string(std::put_time(buf, "%H:%M:%S")._M_fmt);
}
}
