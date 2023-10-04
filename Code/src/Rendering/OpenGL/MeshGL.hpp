#ifndef MESH_GL_HPP
#define MESH_GL_HPP

#include <stdint.h>

#include "glad/glad.h"

#include "Rendering/Renderer.hpp"
#include "Rendering/OpenGL/BuffersGL.hpp"
#include "Rendering/OpenGL/VAOGL.hpp"

namespace Tolik
{
class Debug;

class MeshGL
{
public:
  template<typename T> MeshGL(Vertex *verts, std::size_t vertsCount, T *inds, std::size_t indsCount, const BufferLayoutGL &layout, MeshType meshType = MeshType::Default, GLenum drawMode = GL_TRIANGLES);
  ~MeshGL();

  void Draw();
  inline MeshType GetMeshType() const { return m_meshType; }

private:
  MeshType m_meshType;
  GLenum m_drawMode;
  VAOGL m_vao;
  VBOGL m_vbo;
  EBOGL m_ebo;
};

template<typename T>
inline MeshGL::MeshGL(Vertex *verts, std::size_t vertsCount, T *inds, std::size_t indsCount, const BufferLayoutGL &layout, MeshType meshType, GLenum drawMode)
  : m_meshType(meshType)
  , m_drawMode(drawMode)
{
  m_vbo.BufferData(verts, vertsCount);
  m_ebo.BufferData(inds, indsCount);
  m_vao.AddVBO(m_vbo, layout);
  m_vao.AddEBO(m_ebo);
}

MeshGL::~MeshGL()
{
  m_vao.Delete();
  m_vbo.Delete();
  m_ebo.Delete();
}

void MeshGL::Draw()
{
  m_vao.Bind();
  GL_CALL(glDrawElements(m_drawMode, m_ebo.GetCount(), m_ebo.GetGLType(), 0));
}
}

#endif