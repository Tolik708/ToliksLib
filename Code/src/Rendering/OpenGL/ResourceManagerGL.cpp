#include "Rendering/OpenGL/ResourceManagerGL.hpp"

#include <vector>
#include <unordered_map>
#include <array>
#include <stdint.h>

#include "Rendering/OpenGL/ShaderGL.hpp"
#include "Rendering/Renderer.hpp"

namespace Tolik
{
ResourceManagerGL::ResourceManagerGL()
  : m_indexes
  {
    { MeshType::Default, {0, 0, 1} }
  },
  m_shaders
  {
    ShaderGL("res\\Shaders\\ChunkShader.vert", "res\\Shaders\\ChunkShader.frag")
  },
  m_layouts
  {
    BufferLayoutGL(GL_FLOAT, 3, GL_FALSE, GL_FLOAT, 1, GL_FALSE)
  },
  m_drawModes
  {
    GL_TRIANGLES, GL_QUADS
  }
{}

ResourceManagerGL::~ResourceManagerGL()
{
  for(uint32_t i = 0; i < m_shaders.size(); i++)
    m_shaders[i].Delete();
}
}