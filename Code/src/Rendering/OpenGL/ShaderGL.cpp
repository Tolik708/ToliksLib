#include "Rendering/OpenGL/ShaderGL.hpp"

#include <stdint.h>
#include <string>

#include "glad/glad.h"

#include "Utilities/FileReader.hpp"
#include "Debug/Debug.hpp"

namespace Tolik
{
ShaderGL::ShaderGL(const std::string &vertexShaderPath, const std::string &fragmentShaderPath)
{
  std::string vertexSource, fragmentSource;
  FileReader::ReadTxtFile(vertexShaderPath, vertexSource);
  FileReader::ReadTxtFile(fragmentShaderPath,fragmentSource);

  int succes = 0;
  uint32_t vertexShader, fragmentShader;
  const char *vertexChar = vertexSource.c_str();
  const char *fragmentChar = fragmentSource.c_str();

  GL_CALL(vertexShader = glCreateShader(GL_VERTEX_SHADER));
  GL_CALL(glShaderSource(vertexShader, 1, &vertexChar, NULL));
  GL_CALL(glCompileShader(vertexShader));
  GL_CALL(glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &succes));
  if(!succes)
  {
    char buffer[512];
    GL_CALL(glGetShaderInfoLog(vertexShader, 512, NULL, buffer));
    Debug::GetLogger("main").Error("Error in compiling vertex shader: ", buffer);
  }

  GL_CALL( fragmentShader = glCreateShader(GL_FRAGMENT_SHADER));
  GL_CALL( glShaderSource(fragmentShader, 1, &fragmentChar, NULL));
  GL_CALL( glCompileShader(fragmentShader));
  GL_CALL( glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &succes));
  if(!succes)
  {
    char buffer[512];
    GL_CALL(glGetShaderInfoLog(fragmentShader, 512, NULL, buffer));
    Debug::GetLogger("main").Error("Error in compiling fragment shader: ", buffer);
  }

  GL_CALL(m_id = glCreateProgram());
  GL_CALL(glAttachShader(m_id, vertexShader));
  GL_CALL(glAttachShader(m_id, fragmentShader));
  GL_CALL(glLinkProgram(m_id));
  GL_CALL(glGetProgramiv(m_id, GL_LINK_STATUS, &succes));
  if(!succes)
  {
    char buffer[512];
    GL_CALL(glGetProgramInfoLog(m_id, 512, NULL, buffer));
    Debug::GetLogger("main").Error("Error in linking shaders: ", buffer);
  }

  GL_CALL(glDeleteShader(vertexShader));
  GL_CALL(glDeleteShader(fragmentShader));
}

int ShaderGL::GetLocation(const std::string &name) const
{
  int result = -1;
  GL_CALL(result = glGetUniformLocation(m_id, name.c_str()));
  if(result == -1)
  {
    Debug::GetLogger("main").Error("In call to glGetUniformLocation: name - \"@0\" does not correspond to an active uniform variable in \
    program, name starts with the reserved prefix \"gl_\", or name is associated with an atomic counter or a named uniform block.", name);
    return 0;
  }
  return result;
}
}