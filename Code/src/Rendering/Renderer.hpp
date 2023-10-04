#ifndef RENDERER__HPP
#define RENDERER__HPP

#include <stdint.h>

namespace Tolik
{
class Window;
class Camera;

struct Vertex
{
  Vertex(float newX, float newY, float newZ, int newTexture) : x(newX), y(newY), z(newZ), texture(newTexture) {}

  float x, y, z;
  int texture;
};

/*
 * MeshType is enum that determins what shader and other stuff we will use in creating and rendering mesh
*/
enum class MeshType : uint32_t
{
  Default = 0
};

enum class RenderAPIType : int8_t
{
  OpenGL
};

class Renderer
{
public:
  virtual ~Renderer() = default;

  virtual void StartFrame(const Camera &camera) = 0;
  virtual void RenderMesh(void *mesh) = 0;
  virtual void *CreateMesh(Vertex *verts, std::size_t vertexCount, int8_t *inds, std::size_t indexCount, MeshType meshType)   = 0;
  virtual void *CreateMesh(Vertex *verts, std::size_t vertexCount, uint8_t *inds, std::size_t indexCount, MeshType meshType)  = 0;
  virtual void *CreateMesh(Vertex *verts, std::size_t vertexCount, int16_t *inds, std::size_t indexCount, MeshType meshType)  = 0;
  virtual void *CreateMesh(Vertex *verts, std::size_t vertexCount, uint16_t *inds, std::size_t indexCount, MeshType meshType) = 0;
  virtual void *CreateMesh(Vertex *verts, std::size_t vertexCount, int32_t *inds, std::size_t indexCount, MeshType meshType)  = 0;
  virtual void *CreateMesh(Vertex *verts, std::size_t vertexCount, uint32_t *inds, std::size_t indexCount, MeshType meshType) = 0;
  virtual void *CreateMesh(Vertex *verts, std::size_t vertexCount, int64_t *inds, std::size_t indexCount, MeshType meshType)  = 0;
  virtual void *CreateMesh(Vertex *verts, std::size_t vertexCount, uint64_t *inds, std::size_t indexCount, MeshType meshType) = 0;
  virtual void Debug(void *data) = 0;
  virtual void LockAndHideCursor(bool state) = 0;
  virtual void EndFrame() = 0;

  virtual void SetWindow(Window *window) = 0;
  virtual uint32_t GetSDLWindowFlags() const = 0;
  virtual void UpdateDrawbleSize() = 0;

  inline int GetWidth() const { return m_width; }
  inline int GetHeight() const { return m_height; }

protected:
  int m_width, m_height;
};
}

#endif