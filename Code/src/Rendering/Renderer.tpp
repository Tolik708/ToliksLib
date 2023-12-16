#ifndef RENDERER_TPP
#define RENDERER_TPP

#include "Rendering/OpenGL/MeshGL.hpp"
#include "Rendering/OpenGL/ResourceManagerGL.hpp"
#include "Debug/Debug.hpp"

namespace Tolik
{
// Very important to have this functions inline.
//In ohter case I could have said that O need to sacrifise performance to refuse virtual functions 

inline Renderer::Renderer(RenderAPIType api) : m_api(api)
{
  switch (m_api)
  {
  case RenderAPIType::OpenGL:
    InitGL();
    break;
  default:
    Debug::GetLogger().Error("Unkonown Render API: ", m_api);
  }
}

inline void Renderer::SetWindow(Window *window)
{
  switch (m_api)
  {
  case RenderAPIType::OpenGL:
    SetWindowGL(window);
    break;
  }
}

inline void Renderer::Quit()
{
  switch (m_api)
  {
  case RenderAPIType::OpenGL:
    QuitGL();
    break;
  }
}

inline void Renderer::StartFrame(const Camera &camera) const
{
  switch (m_api)
  {
  case RenderAPIType::OpenGL:
    StartFrameGL(camera);
    break;
  }
}

inline void Renderer::RenderMesh(void *mesh) const
{
  switch (m_api)
  {
  case RenderAPIType::OpenGL:
    RenderMeshGL(static_cast<MeshGL*>(mesh));
    break;
  }
}

inline void Renderer::EndFrame() const
{
  switch (m_api)
  {
  case RenderAPIType::OpenGL:
    EndFrameGL();
    break;
  }
}

template<typename VertexType, typename IndexType>
inline void *Renderer::CreateMesh(MeshType meshType, VertexType *verts, std::size_t vertexCount, IndexType *inds, std::size_t indexCount) const
{
  static_assert(std::is_base_of_v<Vertex, VertexType>, "VertexType passed in \'CreateMesh\' must be of type Vertex or inherit from it");
  switch (m_api)
  {
  case RenderAPIType::OpenGL:
    return CreateMeshGL(meshType, verts, vertexCount, inds, indexCount);
  }

  return nullptr;
}

inline void Renderer::Debug(void *data)
{
  switch (m_api)
  {
  case RenderAPIType::OpenGL:
    DebugGL(static_cast<void*>(data));
    break;
  }
}

inline uint32_t Renderer::GetSDLWindowFlags() const
{
  switch (m_api)
  {
  case RenderAPIType::OpenGL:
    return GetSDLWindowFlagsGL();
  }

  return 0;
}

inline void Renderer::UpdateDrawbleSize()
{
  switch (m_api)
  {
  case RenderAPIType::OpenGL:
    UpdateDrawbleSizeGL();
    break;
  }
}

// Functions that I must define here. Can't wait for modules!

template<typename VertexType, typename IndexType>
inline void *Renderer::CreateMeshGL(MeshType meshType, VertexType *verts, std::size_t vertexCount, IndexType *inds, std::size_t indexCount) const
{
  return new MeshGL(verts, vertexCount, inds, indexCount, static_cast<ResourceManagerGL*>(m_resources), meshType);
}
}


#endif