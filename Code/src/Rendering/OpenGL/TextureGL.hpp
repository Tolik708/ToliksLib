#ifndef TEXTURE_GL_HPP
#define TEXTURE_GL_HPP

#include <string>
#include <stdint.h>
#include <functional>

#include "glad/glad.h"

#include "Debug/Debug.hpp"

namespace Tolik
{
class TextureGL
{
public:
  inline TextureGL();
  
  /* It's really the cleanest solution I came up with
  textureParametrs is a function that contains set of parametrs to set up. Example -
  []()
  {
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
  }
  */
  inline TextureGL(const std::function<void()> &textureParametrs) { GL_CALL(glGenTextures(1, &m_id)); Bind(); textureParametrs(); }

  inline void Delete() { GL_CALL(glDeleteTextures(1, &m_id)); }

  inline void Bind() const { GL_CALL(glBindTexture(GL_TEXTURE_2D, m_id)); }
  inline void Unbind() const { GL_CALL(glBindTexture(GL_TEXTURE_2D, 0)); }

  void BufferTexture(const std::string &path) const;

  bool IsBuffered() { return isBuffered; }
  //std::string GetPath() { return m_path; }

private:
  uint32_t m_id = 0;
  bool isBuffered = false;
  //std::string m_path;
};
}

#endif