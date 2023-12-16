#ifndef BUFFERS_GL_HPP
#define BUFFERS_GL_HPP

#include <stdint.h>

#include "glad/glad.h"

#include "Debug/Debug.hpp"
#include "Rendering/OpenGL/UtilitiesGL.hpp"

namespace Tolik
{
struct Vertex;

class VBOGL
{
public:
  inline VBOGL() { GL_CALL(glGenBuffers(1, &m_id)); }
  inline void Delete() const { GL_CALL(glDeleteBuffers(1, &m_id)); }

  inline void Bind() const { GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_id)); }
  inline void Unbind() const { GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0)); }

  template<typename T>
  inline void BufferData(T *firstElement, std::size_t numberOfElements) const;

private:
  uint32_t m_id;
};


class EBOGL
{
public:
  inline EBOGL() { GL_CALL(glGenBuffers(1, &m_id)); }
  inline void Delete() const { GL_CALL(glDeleteBuffers(1, &m_id)); }

  inline void Bind() const { GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id)); }
  inline void Unbind() const { GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0)); }

  template<typename T>
  inline void BufferData(T *firstElement, std::size_t numberOfElements);
  inline constexpr std::size_t GetCount() { return m_count; }
  inline constexpr GLenum GetGLType() { return m_glType; }

private:
  uint32_t m_id;
  std::size_t m_count;
  GLenum m_glType;
};

template<typename T>
inline void VBOGL::BufferData(T *firstElement, std::size_t numberOfElements) const
{
  Bind();
  GL_CALL(glBufferData(GL_ARRAY_BUFFER, numberOfElements * sizeof(T), firstElement, GL_STATIC_DRAW));
}

template<typename T>
inline void EBOGL::BufferData(T *firstElement, std::size_t numberOfElements)
{
  Bind();
  GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, numberOfElements * sizeof(T), firstElement, GL_STATIC_DRAW));
  m_count = numberOfElements;
  m_glType = GetGLTypeFromType<T>();
}
}

#endif