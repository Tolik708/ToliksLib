#include "RendererGL.hpp"

#include <stdint.h>

#include "glad/glad.h"
#include "SDL2/SDL.h"

#include "Math/Transform.hpp"
#include "Rendering/Window.hpp"
#include "Math/MathFunctions.hpp"
#include "Rendering/Camera.hpp"
#include "Debug/Debug.hpp"
#include "Rendering/OpenGL/ShaderGL.hpp"
#include "Rendering/OpenGL/MeshGL.hpp"
#include "Rendering/OpenGL/ResourceManagerGL.hpp"

namespace Tolik
{
RendererGL::RendererGL()
{
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
}

RendererGL::~RendererGL()
{
  delete resources;
}

void RendererGL::SetWindow(Window *window)
{
  m_window = window;
  SDL_CALL((m_context = SDL_GL_CreateContext(m_window->GetWindow())) != NULL);
  GL_CALL(gladLoadGLLoader(SDL_GL_GetProcAddress));

  UpdateDrawbleSize();
  resources = new ResourceManagerGL();
  GL_CALL(glClearColor(0.2, 0.2, 0.2, 1));
  GL_CALL(glEnable(GL_DEPTH_TEST));
  GL_CALL(glProvokingVertex(GL_LAST_VERTEX_CONVENTION));
  GL_CALL(glViewport(0, 0, m_width, m_height));
}

void RendererGL::StartFrame(const Camera &camera)
{
  GL_CALL(glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT));

  // I decided that fully hardcoded values will be fine
  resources->GetShader(MeshType::Default).SetUniform<4, 4>("u_view", 1, GL_FALSE, &(glm::perspective(DegreesToRadians(camera.FOV), static_cast<float>(m_width) / static_cast<float>(m_height), 0.1f, 1000.0f) * camera.GetViewMatrix())[0][0]);
}

void RendererGL::RenderMesh(void *mesh)
{
  MeshGL *convertedMesh = reinterpret_cast<MeshGL*>(mesh);
  resources->GetShader(convertedMesh->GetMeshType()).Use();
  convertedMesh->Draw();
}

void *RendererGL::CreateMesh(Vertex *verts, std::size_t vertexCount, int8_t *inds, std::size_t indexCount, MeshType meshType)
{ return new MeshGL(verts, vertexCount, inds, indexCount, resources->GetLayout(meshType), meshType, resources->GetDrawMode(meshType)); }
void *RendererGL::CreateMesh(Vertex *verts, std::size_t vertexCount, uint8_t *inds, std::size_t indexCount, MeshType meshType)
{ return new MeshGL(verts, vertexCount, inds, indexCount, resources->GetLayout(meshType), meshType, resources->GetDrawMode(meshType)); }
void *RendererGL::CreateMesh(Vertex *verts, std::size_t vertexCount, int16_t *inds, std::size_t indexCount, MeshType meshType)
{ return new MeshGL(verts, vertexCount, inds, indexCount, resources->GetLayout(meshType), meshType, resources->GetDrawMode(meshType)); }
void *RendererGL::CreateMesh(Vertex *verts, std::size_t vertexCount, uint16_t *inds, std::size_t indexCount, MeshType meshType)
{ return new MeshGL(verts, vertexCount, inds, indexCount, resources->GetLayout(meshType), meshType, resources->GetDrawMode(meshType)); }
void *RendererGL::CreateMesh(Vertex *verts, std::size_t vertexCount, int32_t *inds, std::size_t indexCount, MeshType meshType)
{ return new MeshGL(verts, vertexCount, inds, indexCount, resources->GetLayout(meshType), meshType, resources->GetDrawMode(meshType)); }
void *RendererGL::CreateMesh(Vertex *verts, std::size_t vertexCount, uint32_t *inds, std::size_t indexCount, MeshType meshType)
{ return new MeshGL(verts, vertexCount, inds, indexCount, resources->GetLayout(meshType), meshType, resources->GetDrawMode(meshType)); }
void *RendererGL::CreateMesh(Vertex *verts, std::size_t vertexCount, int64_t *inds, std::size_t indexCount, MeshType meshType)
{ return new MeshGL(verts, vertexCount, inds, indexCount, resources->GetLayout(meshType), meshType, resources->GetDrawMode(meshType)); }
void *RendererGL::CreateMesh(Vertex *verts, std::size_t vertexCount, uint64_t *inds, std::size_t indexCount, MeshType meshType)
{ return new MeshGL(verts, vertexCount, inds, indexCount, resources->GetLayout(meshType), meshType, resources->GetDrawMode(meshType)); }

void RendererGL::Debug(void *data)
{
  
}

void RendererGL::EndFrame()
{
  SDL_GL_SwapWindow(m_window->GetWindow());
}

uint32_t RendererGL::GetSDLWindowFlags() const
{
  return SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;
}

void RendererGL::LockAndHideCursor(bool state)
{
  SDL_SetRelativeMouseMode(state ? SDL_TRUE : SDL_FALSE);
}

void RendererGL::UpdateDrawbleSize()
{
  SDL_GL_GetDrawableSize(m_window->GetWindow(), &m_width, &m_height);
}
}