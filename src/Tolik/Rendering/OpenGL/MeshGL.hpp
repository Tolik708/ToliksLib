#ifndef TOLIK_MESH_GL_HPP
#define TOLIK_MESH_GL_HPP

#include <stdint.h>

#include "Tolik/Setup.hpp"

#include "glad/glad.h"

#include "Tolik/Debug/Debug.hpp"
#include "Tolik/Rendering/Mesh.hpp"
#include "Tolik/Rendering/Renderer.hpp"
#include "Tolik/Rendering/OpenGL/BuffersGL.hpp"
#include "Tolik/Rendering/OpenGL/VAOGL.hpp"
#include "Tolik/Rendering/OpenGL/ResourceManagerGL.hpp"

namespace Tolik
{
class MeshGL : public Mesh
{
public:
  template<typename VertexType, typename IndexType> MeshGL(VertexType *verts, std::size_t vertsCount, IndexType *inds, std::size_t indsCount, ResourceManagerGL *resources, MeshType meshType);
  ~MeshGL()
  {
    m_vao.Delete();
    m_vbo.Delete();
    m_ebo.Delete();
  }

  inline void Draw() const;

private:
  // We save shader and draw mode instead of accesing it by m_resourecs because it's an expensive call
  const ShaderGL shader;
  const uint32_t m_drawMode;

  const VAOGL m_vao;
  const VBOGL m_vbo;
  const EBOGL m_ebo;
};

template<typename VertexType, typename IndexType>
MeshGL::MeshGL(VertexType *verts, std::size_t vertsCount, IndexType *inds, std::size_t indsCount, ResourceManagerGL *resources, MeshType meshType)
  : Mesh(meshType)
  , shader(resources->GetShader(m_meshType))
  , m_drawMode(resources->GetDrawMode(m_meshType))
  , m_vbo(verts, vertsCount)
  , m_ebo(inds, indsCount)
{
  m_vao.AddVBO(m_vbo, resources->GetLayout(m_meshType));
  m_vao.AddEBO(m_ebo);
}

inline void MeshGL::Draw() const
{
  shader.Use();
  m_vao.Bind();
  GL_CALL(glDrawElements(m_drawMode, m_ebo.GetCount(), m_ebo.GetGLType(), 0));
}
}

#endif