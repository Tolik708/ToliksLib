#ifndef RENDERER_GL_HPP
#define RENDERER_GL_HPP

#include <stdint.h>

#include "SDL2/SDl.h"

#include "Rendering/Renderer.hpp"
#include "Rendering/OpenGL/ResourceManagerGL.hpp"

namespace Tolik
{
class Camera;
class Window;

class RendererGL : public Renderer
{
public:
  RendererGL();
  ~RendererGL();
  virtual void SetWindow(Window *window) override;

  virtual void StartFrame(const Camera &camera) override;
  virtual void RenderMesh(void *mesh) override;
  virtual void *CreateMesh(Vertex *verts, std::size_t vertexCount, int8_t *inds, std::size_t indexCount, MeshType meshType)   override;
  virtual void *CreateMesh(Vertex *verts, std::size_t vertexCount, uint8_t *inds, std::size_t indexCount, MeshType meshType)  override;
  virtual void *CreateMesh(Vertex *verts, std::size_t vertexCount, int16_t *inds, std::size_t indexCount, MeshType meshType)  override;
  virtual void *CreateMesh(Vertex *verts, std::size_t vertexCount, uint16_t *inds, std::size_t indexCount, MeshType meshType) override;
  virtual void *CreateMesh(Vertex *verts, std::size_t vertexCount, int32_t *inds, std::size_t indexCount, MeshType meshType)  override;
  virtual void *CreateMesh(Vertex *verts, std::size_t vertexCount, uint32_t *inds, std::size_t indexCount, MeshType meshType) override;
  virtual void *CreateMesh(Vertex *verts, std::size_t vertexCount, int64_t *inds, std::size_t indexCount, MeshType meshType)  override;
  virtual void *CreateMesh(Vertex *verts, std::size_t vertexCount, uint64_t *inds, std::size_t indexCount, MeshType meshType) override;
  virtual void Debug(void *data) override;
  virtual void LockAndHideCursor(bool state) override;
  virtual void EndFrame() override;

  virtual uint32_t GetSDLWindowFlags() const override;
  virtual void UpdateDrawbleSize() override;
  
private:
  Window *m_window;
  SDL_GLContext m_context;
  ResourceManagerGL *resources;
};
}

#endif