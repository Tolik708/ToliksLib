#ifndef MESH_HPP
#define MESH_HPP

#include <stdint.h>

namespace Tolik
{
enum class MeshType : uint32_t;

class Mesh
{
public:
  inline constexpr MeshType GetMeshType() const { return m_meshType; }

protected:
  Mesh(const MeshType meshType) : m_meshType(meshType) {}

  const MeshType m_meshType;
};
}

#endif