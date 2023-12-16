#include "Rendering/OpenGL/TextureGL.hpp"

#include <string>
#include <stdint.h>

#include "glad/glad.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Debug/Debug.hpp"

namespace Tolik
{
inline TextureGL::TextureGL()
{
  GL_CALL(glGenTextures(1, &m_id));

  Bind();
  GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));	
  GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
  GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
  GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
}

void TextureGL::BufferTexture(const std::string &path) const
{
  //m_path = path;

  int height, width;
  uint8_t *data = stbi_load(path.c_str(), &width, &height, nullptr, STBI_rgb);

  if(!data)
    return Debug::GetLogger().Error("Failed to load texture: ", path);

  Bind();
  GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data));

  stbi_image_free(data);
}
}
