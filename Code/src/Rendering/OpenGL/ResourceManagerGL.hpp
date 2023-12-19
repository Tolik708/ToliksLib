#ifndef RESOURCE_MANAGER_GL_HPP
#define RESOURCE_MANAGER_GL_HPP

#include <vector>
#include <unordered_map>
#include <array>
#include <stdint.h>

#include "glad/glad.h"

#include "Rendering/OpenGL/ShaderGL.hpp"
#include "Rendering/OpenGL/VAOGL.hpp"


namespace Tolik
{
class Debug;
enum class MeshType : uint32_t;

class ResourceManagerGL
{
public:
  ResourceManagerGL();
  ~ResourceManagerGL();
  const ShaderGL &GetShader(MeshType meshType) const { return m_shaders[m_indexes.at(meshType)[0]]; }
  const BufferLayoutGL &GetLayout(MeshType meshType) const { return m_layouts[m_indexes.at(meshType)[1]]; }
  uint32_t GetDrawMode(MeshType meshType) const { return m_drawModes[m_indexes.at(meshType)[2]]; }
  const TextureGL &GetTexture(MeshType meshType) const { return m_textures[m_indexes.at(meshType)[3]]; }

private:
  // 0 - Shader
  // 1 - Buffer Layout
  std::unordered_map<MeshType, std::array<uint32_t, 4>> m_indexes;
  
  std::vector<ShaderGL> m_shaders;
  std::vector<BufferLayoutGL> m_layouts;
  std::vector<uint32_t> m_drawModes;
  std::vector<TextureGL> m_textures;
};
}

#endif