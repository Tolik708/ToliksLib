#ifndef SHADER_GL_HPP
#define SHADER_GL_HPP

#include <stdint.h>
#include <string>

#include "glad/glad.h"

#include "Utilities/FileReader.hpp"
#include "Debug/Debug.hpp"

namespace Tolik
{
class Debug;

class ShaderGL
{
public:
  ShaderGL(const std::string &vertexShaderPath, const std::string &fragmentShaderPath);
  inline void Delete() const { GL_CALL(glDeleteProgram(m_id)); }

  inline void Use() const { GL_CALL(glUseProgram(m_id)); }
  template<typename... Args> inline void SetUniform(const std::string &name, Args... args) const { Debug::GetLogger("main").Error("No overload of ShaderGL::SetUniform with this parametrs exist! In @0", __PRETTY_FUNCTION__); }
  template<std::size_t N, typename T> inline void SetUniform(const std::string &name, std::size_t count, const T *value) const { Debug::GetLogger("main").Error("No overload of ShaderGL::SetUniform with this parametrs exist! In @0", __PRETTY_FUNCTION__); }
  template<std::size_t N1, std::size_t N2> inline void SetUniform(const std::string &name, std::size_t count, unsigned char transpose, const float *value) const { Debug::GetLogger("main").Error("No overload of ShaderGL::SetUniform with this parametrs exist! In @0", __PRETTY_FUNCTION__); }

  inline bool operator!=(const ShaderGL &other) { return m_id != other.m_id; }

private:
  int GetLocation(const std::string &name) const;

  uint32_t m_id;
};
}

#include "ShaderGL.tpp"

#endif