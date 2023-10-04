#include "Debug/Debug.hpp"

#include <unordered_map>
#include <string>

#include "glad/glad.h"

#include "Debug/Logger.hpp"

namespace Tolik
{
const bool Debug::showSDLEvents = false;

const std::unordered_map<GLenum, std::string> Debug::GLErrorsNamesMap =
{
	{ GL_NO_ERROR,                      "GL_NO_ERROR" },
	{ GL_INVALID_ENUM,                  "GL_INVALID_ENUM" },
	{ GL_INVALID_VALUE,                 "GL_INVALID_VALUE" },
	{ GL_INVALID_OPERATION,             "GL_INVALID_OPERATION"} ,
	{ GL_INVALID_FRAMEBUFFER_OPERATION, "GL_INVALID_FRAMEBUFFER_OPERATION" },
	{ GL_OUT_OF_MEMORY,                 "GL_OUT_OF_MEMORY" },
	{ GL_STACK_UNDERFLOW,               "GL_STACK_UNDERFLOW" },
	{ GL_STACK_OVERFLOW,                "GL_STACK_OVERFLOW" }
};

Debug Debug::s_instance = Debug();

Debug::Debug()
{
  AddLogger("main", Logger("[@T] @M\n"));
}

void Debug::AddLogger(const std::string &name, const Logger &logger)
{
	std::unordered_map<std::string, Logger>::iterator it = s_instance.m_loggers.find(name);
	if(it != s_instance.m_loggers.end())
	{
		GetLogger("main").Error("Logger with name: \'@0\', already exists", name);
		return;
	}
	s_instance.m_loggers.emplace_hint(it, name, logger);
}

Logger &Debug::GetLogger(const std::string &name)
{
  std::unordered_map<std::string, Logger>::iterator it = s_instance.m_loggers.find(name);
	if(it == s_instance.m_loggers.end())
	{
		GetLogger("main").Error("No logger with name: \'@0\'", name);
		return s_instance.m_loggers.at("main");
	}
	return it->second;
}
}