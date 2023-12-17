#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <stdint.h>
// std::size_t
#include <cstddef>
#include "Math/Constants.hpp"

namespace Tolik
{
class Window;
class Camera;
class MeshGL;

struct Vertex
{
  Vertex(DefFloatType newX, DefFloatType newY, DefFloatType newZ) : x(newX), y(newY), z(newZ) {}
  
  DefFloatType x, y, z;
};

struct DefaultVertex : Vertex
{
  DefaultVertex(DefFloatType newX, DefFloatType newY, DefFloatType newZ, DefFloatType newU, DefFloatType newV) : Vertex(newX, newY, newZ), u(newU), v(newV) {}

  DefFloatType u, v;
};

// MeshType is enum that determins what shader and other stuff we will use in creating and rendering mesh
enum class MeshType : uint32_t;

enum class RenderAPIType : int8_t
{
  OpenGL
};

// Yes. I know about virtual functions, but a) they meight be slower; b) you can't use templates

class Renderer
{
public:
  // First initialization phase (before creating window)
  inline Renderer(RenderAPIType api);
  // Second initialization phase (after creating window)
  inline void SetWindow(Window *window);
  // Couldn't use destructor because we need to control order of destruction in Window class
  inline void Quit();

  inline void StartFrame(const Camera &camera) const;
  inline void RenderMesh(void *mesh) const;
  inline void EndFrame() const;

  template<typename VertexType, typename IndexType> inline void *CreateMesh(MeshType meshType, VertexType *verts, std::size_t vertexCount, IndexType *inds, std::size_t indexCount) const;
  
  // Function for debugging. Expected to use const_cast to acces this function
  inline void Debug(void *data);
  inline uint32_t GetSDLWindowFlags() const;
  inline void UpdateDrawbleSize();

  inline constexpr int GetDrawbleWidth() const { return m_width; }
  inline constexpr int GetDrawbleHeight() const { return m_height; }

private:
  // GL implementations

  void InitGL();
  void SetWindowGL(Window *window);

  void QuitGL();

  void StartFrameGL(const Camera &camera) const;
  void RenderMeshGL(MeshGL *mesh) const;
  void EndFrameGL() const;

  template<typename VertexType, typename IndexType> inline void *CreateMeshGL(MeshType meshType, VertexType *verts, std::size_t vertexCount, IndexType *inds, std::size_t indexCount) const;

  void DebugGL(void *data) const;
  void UpdateDrawbleSizeGL();
  uint32_t GetSDLWindowFlagsGL() const;


  const RenderAPIType m_api;
  int m_width, m_height;
  void *m_resources;
  void *m_context;
  Window *m_window;
};
}

#include "Renderer.tpp"

#endif