#ifndef MESH_GL_HPP
#define MESH_GL_HPP

#include <stdint.h>

#include "glad/glad.h"

#include "Rendering/Renderer.hpp"
#include "Rendering/OpenGL/BuffersGL.hpp"
#include "Rendering/OpenGL/VAOGL.hpp"
#include "Rendering/OpenGL/ResourceManagerGL.hpp"

namespace Tolik
{
class Debug;

class MeshGL
{
public:
  template<typename VertexType, typename IndexType> inline MeshGL(VertexType *verts, std::size_t vertsCount, IndexType *inds, std::size_t indsCount, ResourceManagerGL *resources, MeshType meshType);
  inline ~MeshGL();

  inline void Draw();
  inline constexpr MeshType GetMeshType() const { return m_meshType; }

private:
  const MeshType m_meshType;
  // We save shader and draw mode instead of accesing it by m_resourecs because it is expensive call
  const ShaderGL shader;
  const GLenum m_drawMode;
  const VAOGL m_vao;
  const VBOGL m_vbo;
  
  EBOGL m_ebo;

};

template<typename VertexType, typename IndexType>
inline MeshGL::MeshGL(VertexType *verts, std::size_t vertsCount, IndexType *inds, std::size_t indsCount, ResourceManagerGL *resources, MeshType meshType)
  : m_meshType(meshType)
  , shader(resources->GetShader(m_meshType))
  , m_drawMode(resources->GetDrawMode(m_meshType))
{
  m_vbo.BufferData(verts, vertsCount);
  m_ebo.BufferData(inds, indsCount);
  m_vao.AddVBO(m_vbo, resources->GetLayout(m_meshType));
  m_vao.AddEBO(m_ebo);
}

inline MeshGL::~MeshGL()
{
  m_vao.Delete();
  m_vbo.Delete();
  m_ebo.Delete();
}

inline void MeshGL::Draw()
{
  shader.Use();
  m_vao.Bind();
  GL_CALL(glDrawElements(m_drawMode, m_ebo.GetCount(), m_ebo.GetGLType(), 0));
}
}

#endif