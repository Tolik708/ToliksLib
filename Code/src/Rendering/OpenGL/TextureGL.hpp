#ifndef TEXTURE_GL_HPP
#define TEXTURE_GL_HPP

#include <string>
#include <stdint.h>
#include <tuple>
#include <utility>

#include "glad/glad.h"

#include "Debug/Debug.hpp"

#define BIT(x) (1 << x)

namespace Tolik
{
enum class TextureFlags
{
  NONE = 0,

  GenerateMipmap = BIT(0),
};

class TextureGL
{
public:
  TextureGL(uint32_t textureType, TextureFlags textureFlags) : m_type(textureType), m_flags(textureFlags)
  { GL_CALL(glGenTextures(1, &m_id)); }
  template<typename... Args> TextureGL(uint32_t textureType, const std::string &path) : m_type(textureType)
  { GL_CALL(glGenTextures(1, &m_id)); BufferData(path); }
  template<typename... Args> TextureGL(uint32_t textureType, const std::tuple<Args...> &textureParametrs) : m_type(textureType)
  { GL_CALL(glGenTextures(1, &m_id)); SetParametrs(textureParametrs); }
  template<typename... Args> TextureGL(uint32_t textureType, const std::string &path, const std::tuple<Args...> &textureParametrs) : m_type(textureType)
  { GL_CALL(glGenTextures(1, &m_id)); SetParametrs(textureParametrs); BufferData(path); }

  inline void Delete() { GL_CALL(glDeleteTextures(1, &m_id)); }

  inline void Bind() const { GL_CALL(glBindTexture(m_type, m_id)); }
  inline void Unbind() const { GL_CALL(glBindTexture(m_type, 0)); }

  void BufferData(const std::string &path);
  template<std::size_t Index = 0, typename... Args> void SetParametrs(const std::tuple<std::pair<uint32_t, Args>...> &textureParametrs) const;
  template<typename T> inline void SetParametr(uint32_t parametrName, T parametr) const { Debug::GetLogger().Error("No function to set glTexParametr with parametr of type \'@0\'", typeid(T).name()); }

  inline bool IsBuffered() { return m_isBuffered; }
  inline uint32_t GetType() { return m_type; }
  inline TextureFlags GetFlags() { return m_flags; }
  //inline std::string GetPath() { return m_path; }

private:
  uint32_t m_id = 0;
  uint32_t m_type = 0;
  TextureFlags m_flags;
  bool m_isBuffered = false;
  //std::string m_path;
};
}

#endif