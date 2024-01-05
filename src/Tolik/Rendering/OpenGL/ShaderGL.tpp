#ifndef TOLIK_SHADER_GL_TPP
#define TOLIK_SHADER_GL_TPP

#ifndef TOLIK_SHADER_GL_HPP
#error __FILE__ should only be included from ShaderGL.hpp
#endif

namespace Tolik
{
template<> inline void ShaderGL::SetUniform<int>(const std::string &name, int value0) const
{ Use(); GL_CALL(glUniform1i(GetLocation(name), value0)); }
template<> inline void ShaderGL::SetUniform<int, int>(const std::string &name, int value0, int value1) const
{ Use(); GL_CALL(glUniform2i(GetLocation(name), value0, value1)); }
template<> inline void ShaderGL::SetUniform<int, int, int>(const std::string &name, int value0, int value1, int value2) const
{ Use(); GL_CALL(glUniform3i(GetLocation(name), value0, value1, value2)); }
template<> inline void ShaderGL::SetUniform<int, int, int, int>(const std::string &name, int value0, int value1, int value2, int value3) const
{ Use(); GL_CALL(glUniform4i(GetLocation(name), value0, value1, value2, value3)); }

template<> inline void ShaderGL::SetUniform<float>(const std::string &name, float value0) const
{ Use(); GL_CALL(glUniform1f(GetLocation(name), value0)); }
template<> inline void ShaderGL::SetUniform<float, float>(const std::string &name, float value0, float value1) const
{ Use(); GL_CALL(glUniform2f(GetLocation(name), value0, value1)); }
template<> inline void ShaderGL::SetUniform<float, float, float>(const std::string &name, float value0, float value1, float value2) const
{ Use(); GL_CALL(glUniform3f(GetLocation(name), value0, value1, value2)); }
template<> inline void ShaderGL::SetUniform<float, float, float, float>(const std::string &name, float value0, float value1, float value2, float value3) const
{ Use(); GL_CALL(glUniform4f(GetLocation(name), value0, value1, value2, value3)); }

template<> inline void ShaderGL::SetUniform<uint32_t>(const std::string &name, uint32_t value0) const
{ Use(); GL_CALL(glUniform1ui(GetLocation(name), value0)); }
template<> inline void ShaderGL::SetUniform<uint32_t, uint32_t>(const std::string &name, uint32_t value0, uint32_t value1) const
{ Use(); GL_CALL(glUniform2ui(GetLocation(name), value0, value1)); }
template<> inline void ShaderGL::SetUniform<uint32_t, uint32_t, uint32_t>(const std::string &name, uint32_t value0, uint32_t value1, uint32_t value2) const
{ Use(); GL_CALL(glUniform3ui(GetLocation(name), value0, value1, value2)); }
template<> inline void ShaderGL::SetUniform<uint32_t, uint32_t, uint32_t, uint32_t>(const std::string &name, uint32_t value0, uint32_t value1, uint32_t value2, uint32_t value3) const
{ Use(); GL_CALL(glUniform4ui(GetLocation(name), value0, value1, value2, value3)); }

template<> inline void ShaderGL::SetUniform<1, int>(const std::string &name, std::size_t count, const int *value) const
{ Use(); GL_CALL(glUniform1iv(GetLocation(name), count, value)); }
template<> inline void ShaderGL::SetUniform<2, int>(const std::string &name, std::size_t count, const int *value) const
{ Use(); GL_CALL(glUniform2iv(GetLocation(name), count, value)); }
template<> inline void ShaderGL::SetUniform<3, int>(const std::string &name, std::size_t count, const int *value) const
{ Use(); GL_CALL(glUniform3iv(GetLocation(name), count, value)); }
template<> inline void ShaderGL::SetUniform<4, int>(const std::string &name, std::size_t count, const int *value) const
{ Use(); GL_CALL(glUniform4iv(GetLocation(name), count, value)); }

template<> inline void ShaderGL::SetUniform<1, float>(const std::string &name, std::size_t count, const float *value) const
{ Use(); GL_CALL(glUniform1fv(GetLocation(name), count, value)); }
template<> inline void ShaderGL::SetUniform<2, float>(const std::string &name, std::size_t count, const float *value) const
{ Use(); GL_CALL(glUniform2fv(GetLocation(name), count, value)); }
template<> inline void ShaderGL::SetUniform<3, float>(const std::string &name, std::size_t count, const float *value) const
{ Use(); GL_CALL(glUniform3fv(GetLocation(name), count, value)); }
template<> inline void ShaderGL::SetUniform<4, float>(const std::string &name, std::size_t count, const float *value) const
{ Use(); GL_CALL(glUniform4fv(GetLocation(name), count, value)); }

template<> inline void ShaderGL::SetUniform<1, uint32_t>(const std::string &name, std::size_t count, const uint32_t *value) const
{ Use(); GL_CALL(glUniform1uiv(GetLocation(name), count, value)); }
template<> inline void ShaderGL::SetUniform<2, uint32_t>(const std::string &name, std::size_t count, const uint32_t *value) const
{ Use(); GL_CALL(glUniform2uiv(GetLocation(name), count, value)); }
template<> inline void ShaderGL::SetUniform<3, uint32_t>(const std::string &name, std::size_t count, const uint32_t *value) const
{ Use(); GL_CALL(glUniform3uiv(GetLocation(name), count, value)); }
template<> inline void ShaderGL::SetUniform<4, uint32_t>(const std::string &name, std::size_t count, const uint32_t *value) const
{ Use(); GL_CALL(glUniform4uiv(GetLocation(name), count, value)); }

template<> inline void ShaderGL::SetUniform<2, 2>(const std::string &name, std::size_t count, unsigned char transpose, const float *value) const
{ Use(); GL_CALL(glUniformMatrix2fv(GetLocation(name), count, transpose, value)); }
template<> inline void ShaderGL::SetUniform<3, 3>(const std::string &name, std::size_t count, unsigned char transpose, const float *value) const
{ Use(); GL_CALL(glUniformMatrix3fv(GetLocation(name), count, transpose, value)); }
template<> inline void ShaderGL::SetUniform<4, 4>(const std::string &name, std::size_t count, unsigned char transpose, const float *value) const
{ Use(); GL_CALL(glUniformMatrix4fv(GetLocation(name), count, transpose, value)); }

template<> inline void ShaderGL::SetUniform<2, 3>(const std::string &name, std::size_t count, unsigned char transpose, const float *value) const
{ Use(); GL_CALL(glUniformMatrix2x3fv(GetLocation(name), count, transpose, value)); }
template<> inline void ShaderGL::SetUniform<3, 2>(const std::string &name, std::size_t count, unsigned char transpose, const float *value) const
{ Use(); GL_CALL(glUniformMatrix3x2fv(GetLocation(name), count, transpose, value)); }
template<> inline void ShaderGL::SetUniform<4, 2>(const std::string &name, std::size_t count, unsigned char transpose, const float *value) const
{ Use(); GL_CALL(glUniformMatrix4x2fv(GetLocation(name), count, transpose, value)); }
template<> inline void ShaderGL::SetUniform<2, 4>(const std::string &name, std::size_t count, unsigned char transpose, const float *value) const
{ Use(); GL_CALL(glUniformMatrix2x4fv(GetLocation(name), count, transpose, value)); }
template<> inline void ShaderGL::SetUniform<3, 4>(const std::string &name, std::size_t count, unsigned char transpose, const float *value) const
{ Use(); GL_CALL(glUniformMatrix3x4fv(GetLocation(name), count, transpose, value)); }
template<> inline void ShaderGL::SetUniform<4, 3>(const std::string &name, std::size_t count, unsigned char transpose, const float *value) const
{ Use(); GL_CALL(glUniformMatrix4x3fv(GetLocation(name), count, transpose, value)); }
}

#endif