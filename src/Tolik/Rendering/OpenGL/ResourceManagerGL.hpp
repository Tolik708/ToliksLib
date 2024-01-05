#ifndef TOLIK_RESOURCE_MANAGER_GL_HPP
#define TOLIK_RESOURCE_MANAGER_GL_HPP

#include <vector>
#include <unordered_map>
#include <array>
#include <stdint.h>

#include "Tolik/Setup.hpp"

#include "glad/glad.h"

#include "Tolik/Rendering/OpenGL/ShaderGL.hpp"
#include "Tolik/Rendering/OpenGL/VAOGL.hpp"
#include "Tolik/Rendering/OpenGL/TextureGL.hpp"


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
  const std::vector<TextureGL> &GetTexture(MeshType meshType) const { return m_textures[m_indexes.at(meshType)[3]]; }

private:
  /*
    0 - Shader
    1 - Buffer Layout
    2 - Draw Mode
    3 - Textures / Texture atlas
  */
  std::unordered_map<MeshType, std::array<uint32_t, 4>> m_indexes;
  
  std::vector<ShaderGL> m_shaders;
  std::vector<BufferLayoutGL> m_layouts;
  std::vector<uint32_t> m_drawModes;
  std::vector<std::vector<TextureGL>> m_textures;
};
}

#endif