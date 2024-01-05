#ifndef TOLIK_VECTOR_DECLARATION_HPP
#define TOLIK_VECTOR_DECLARATION_HPP

/*
  Small file to forward declarate Vector class
*/

#include <stdint.h>
#include <cstddef>

#include "Tolik/Setup.hpp"

#include "Tolik/Math/Constants.hpp"

namespace Tolik
{
enum class VectorFlag : uint8_t
{
  NONE = 0,

  Vector,
  Quaternion,
  Color,
};

template<typename Type, std::size_t Size, VectorFlag Group = VectorFlag::Vector> class Vector;

template<typename> constexpr bool IsVectorClass = false;

template<typename T1, auto A1, auto A2>
constexpr bool IsVectorClass<Vector<T1, A1, A2>> = true;


using Qua = Vector<DefFloatType, 4, VectorFlag::Quaternion>;
template<typename Type> using QuaT = Vector<Type, 4, VectorFlag::Quaternion>;

using Color32 = Vector<uint8_t, 4, VectorFlag::Color>;
using Color24 = Vector<uint8_t, 3, VectorFlag::Color>;
using UnitColor = Vector<DefFloatType, 4, VectorFlag::Color>;
template<typename Type, std::size_t Size> using Color = Vector<Type, Size, VectorFlag::Color>;

using Vec4 = Vector<DefFloatType, 4, VectorFlag::Vector>;
using Vec3 = Vector<DefFloatType, 3, VectorFlag::Vector>;
using Vec2 = Vector<DefFloatType, 2, VectorFlag::Vector>;
using Vec1 = Vector<DefFloatType, 1, VectorFlag::Vector>;
using Vec4i = Vector<DefIntType, 4, VectorFlag::Vector>;
using Vec3i = Vector<DefIntType, 3, VectorFlag::Vector>;
using Vec2i = Vector<DefIntType, 2, VectorFlag::Vector>;
using Vec1i = Vector<DefIntType, 1, VectorFlag::Vector>;
template<typename Type> using Vec4T = Vector<Type, 4, VectorFlag::Vector>;
template<typename Type> using Vec3T = Vector<Type, 3, VectorFlag::Vector>;
template<typename Type> using Vec2T = Vector<Type, 2, VectorFlag::Vector>;
template<typename Type> using Vec1T = Vector<Type, 1, VectorFlag::Vector>;
template<typename Type, std::size_t Size> using Vec = Vector<Type, Size, VectorFlag::Vector>;
}

#endif