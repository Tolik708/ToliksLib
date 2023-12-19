#include "Rendering/OpenGL/TextureGL.hpp"

#include <string>
#include <stdint.h>
#include <tuple>
#include <utility>

#include "glad/glad.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Debug/Debug.hpp"

namespace Tolik
{
void TextureGL::BufferData(const std::string &path)
{
  //m_path = path;
  m_isBuffered = true;

  int height, width, depth;
  // TODO: own function to read files
  uint8_t *data = stbi_load(path.c_str(), &width, &height, nullptr, STBI_rgb);

  if(!data)
    return Debug::GetLogger().Error("Failed to load texture: ", path);

  Bind();
  switch(m_type)
  {
  case GL_TEXTURE_1D:
  case GL_PROXY_TEXTURE_1D:
    GL_CALL(glTexImage1D(GL_TEXTURE_2D, 0, GL_RGB, width, 0, GL_RGB, GL_UNSIGNED_BYTE, data));
  }
  GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data));
  if(m_flags & TextureFlags::GenerateMipmap)
    glGenerateMipmap(m_type);

  stbi_image_free(data);
}
}
