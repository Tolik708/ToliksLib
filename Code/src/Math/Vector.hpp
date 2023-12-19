#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <type_traits>
#include <limits>
#include <math.h>
#include <iostream>
#include <stdint.h>

#include "Utilities/TypeFunctions.hpp"
#include "Utilities/HashFunctions.hpp"
#include "Math/MathFunctions.hpp"
#include "Math/Constants.hpp"
#include "Debug/Debug.hpp"

namespace Tolik
{
// Option for constructor to accept one number not as scalar
class NonScalar;

enum class VectorFlag
{
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


namespace Detail
{
  // Min and Max
  template<typename Type, std::size_t Size, VectorFlag Group, bool IsArithmetic = std::numeric_limits<Type>::is_specialized> struct MinMaxConstants
  {
    static inline constexpr Vector<Type, Size, Group> min();
    static inline constexpr Vector<Type, Size, Group> max();
  };

  template<typename Type, std::size_t Size, VectorFlag Group> struct MinMaxConstants<Type, Size, Group, false> {};

  template<typename Type, std::size_t Size, std::size_t Index> struct DirectionalConstants {};
  template<typename Type, std::size_t Size> struct DirectionalConstants<Type, Size, 1>
  {
    static inline constexpr Vector<Type, Size, VectorFlag::Vector> right();
    static inline constexpr Vector<Type, Size, VectorFlag::Vector> left();
  };

  template<typename Type, std::size_t Size> struct DirectionalConstants<Type, Size, 2> : DirectionalConstants<Type, Size, 1>
  {
    static inline constexpr Vector<Type, Size, VectorFlag::Vector> up();
    static inline constexpr Vector<Type, Size, VectorFlag::Vector> down();
  };

  template<typename Type, std::size_t Size> struct DirectionalConstants<Type, Size, 3> : DirectionalConstants<Type, Size, 2>
  {
    static inline constexpr Vector<Type, Size, VectorFlag::Vector> forward();
    static inline constexpr Vector<Type, Size, VectorFlag::Vector> backward();
  };

  template<typename Type, std::size_t Size> struct DirectionalConstants<Type, Size, 4> : DirectionalConstants<Type, Size, 3> {};
  
  template<typename Type, std::size_t Size, VectorFlag Group> struct VectorConstants {};

  // Vector
  template<typename Type, std::size_t Size> struct VectorConstants<Type, Size, VectorFlag::Vector> : DirectionalConstants<Type, Size, Size> {};

  // Quaternion
  template<typename Type> struct VectorConstants<Type, 4, VectorFlag::Quaternion>
  {
    static inline constexpr QuaT<Type> identity();
  };

  // Color24
  template<> struct VectorConstants<uint8_t, 3, VectorFlag::Color>
  {
    static inline constexpr Color24 black();
    static inline constexpr Color24 white();
  };

  // Color32
  template<> struct VectorConstants<uint8_t, 4, VectorFlag::Color>
  {
    static inline constexpr Color32 black();
    static inline constexpr Color32 white();
  };

  // Unit Color
  template<> struct VectorConstants<DefFloatType, 4, VectorFlag::Color>
  {
    static inline constexpr UnitColor black();
    static inline constexpr UnitColor white();
  };
}


template<typename Type, std::size_t Size, VectorFlag Group> struct Vector : public Detail::VectorConstants<Type, Size, Group>, public Detail::MinMaxConstants<Type, Size, Group>
{
  static_assert(Size != 0, "Vector can't be of Size 0");
  static_assert((Group == VectorFlag::Quaternion) ? Size == 4 : true, "Quaternion can't be of Size != 4");

  using Self = Vector<Type, Size, Group>;
  using ValueType = Type;
  using SizeType = std::size_t;
  using GroupType = VectorFlag;
  inline constexpr static bool isQuaternion = Group == VectorFlag::Quaternion;
  inline constexpr static bool isColor = Group == VectorFlag::Color;
  inline constexpr static bool isVector = Group == VectorFlag::Vector;
  inline constexpr static VectorFlag group = Group;
  inline constexpr static std::size_t size = Size;
  
  std::array<Type, Size> data = {};

  // Constructors
  
  constexpr Vector() = default;
  constexpr Vector(const std::array<Type, Size> &newArray) : data(newArray) {}
  constexpr Vector(std::array<Type, Size> &&newArray) : data(std::move(newArray)) {}
  template<typename std::enable_if_t<Size != 1, bool> = true> constexpr Vector(Type scalar) { for(std::size_t i = 0; i < Size; i++) data[i] = static_cast<Type>(scalar); }
  template<typename... Args, typename std::enable_if_t<(sizeof...(Args) <= Size), bool> = true> constexpr Vector(Args... args) : data { static_cast<Type>(args)... } {}
  template<typename... Args, typename std::enable_if_t<(sizeof...(Args) <= Size), bool> = true> constexpr Vector(Identity<NonScalar>, Args... args) : data{ static_cast<Type>(args)... } {}

  // For some reason std::enable_if can't see Size without helper var 'S'.

  template<typename VectorType, VectorFlag VectorGroup> constexpr Vector(const Vector<VectorType, 1, VectorGroup> &vector) : data{ static_cast<Type>(vector.x()) } {}
  template<typename VectorType, VectorFlag VectorGroup, std::size_t S = Size, std::enable_if_t< S == 1, bool> = true> constexpr Vector(const Vector<VectorType, 2, VectorGroup> &vector) : data{ static_cast<Type>(vector.x()) } {}
  template<typename VectorType, VectorFlag VectorGroup, std::size_t S = Size, std::enable_if_t<(S > 1), bool> = true> constexpr Vector(const Vector<VectorType, 2, VectorGroup> &vector) : data{ static_cast<Type>(vector.x()), static_cast<Type>(vector.y()) } {}
  template<typename VectorType, VectorFlag VectorGroup, std::size_t S = Size, std::enable_if_t< S == 1, bool> = true> constexpr Vector(const Vector<VectorType, 3, VectorGroup> &vector) : data{ static_cast<Type>(vector.x()) } {}
  template<typename VectorType, VectorFlag VectorGroup, std::size_t S = Size, std::enable_if_t< S == 2, bool> = true> constexpr Vector(const Vector<VectorType, 3, VectorGroup> &vector) : data{ static_cast<Type>(vector.x()), static_cast<Type>(vector.y()) } {}
  template<typename VectorType, VectorFlag VectorGroup, std::size_t S = Size, std::enable_if_t<(S > 2), bool> = true> constexpr Vector(const Vector<VectorType, 3, VectorGroup> &vector) : data{ static_cast<Type>(vector.x()), static_cast<Type>(vector.y()), static_cast<Type>(vector.z()) } {}
  template<typename VectorType, VectorFlag VectorGroup, std::size_t S = Size, std::enable_if_t< S == 1, bool> = true> constexpr Vector(const Vector<VectorType, 4, VectorGroup> &vector) : data{ static_cast<Type>(vector.x()) } {}
  template<typename VectorType, VectorFlag VectorGroup, std::size_t S = Size, std::enable_if_t< S == 2, bool> = true> constexpr Vector(const Vector<VectorType, 4, VectorGroup> &vector) : data{ static_cast<Type>(vector.x()), static_cast<Type>(vector.y()) } {}
  template<typename VectorType, VectorFlag VectorGroup, std::size_t S = Size, std::enable_if_t< S == 3, bool> = true> constexpr Vector(const Vector<VectorType, 4, VectorGroup> &vector) : data{ static_cast<Type>(vector.x()), static_cast<Type>(vector.y()), static_cast<Type>(vector.z()) } {}
  template<typename VectorType, VectorFlag VectorGroup, std::size_t S = Size, std::enable_if_t<(S > 3), bool> = true> constexpr Vector(const Vector<VectorType, 4, VectorGroup> &vector) : data{ static_cast<Type>(vector.x()), static_cast<Type>(vector.y()), static_cast<Type>(vector.z()), static_cast<Type>(vector.w()) } {}

  template<typename VectorType, VectorFlag VectorGroup, std::size_t S = Size, typename T1, std::enable_if_t<S == 2, bool> = true> constexpr Vector(const Vector<VectorType, 1, VectorGroup> &vector, T1 t1) : data{ static_cast<Type>(vector.x()), static_cast<Type>(t1) } {}
  template<typename VectorType, VectorFlag VectorGroup, std::size_t S = Size, typename T1, std::enable_if_t<S == 2, bool> = true> constexpr Vector(T1 t1, const Vector<VectorType, 1, VectorGroup> &vector) : data{ static_cast<Type>(t1), static_cast<Type>(vector.x()) } {}
  template<typename VectorType, VectorFlag VectorGroup, std::size_t S = Size, typename T1, typename T2, std::enable_if_t<S == 3, bool> = true> constexpr Vector(const Vector<VectorType, 1, VectorGroup> &vector, T1 t1, T2 t2) : data{ static_cast<Type>(vector.x()), static_cast<Type>(t1), static_cast<Type>(t2) } {}
  template<typename VectorType, VectorFlag VectorGroup, std::size_t S = Size, typename T1, typename T2, std::enable_if_t<S == 3, bool> = true> constexpr Vector(T1 t1, T2 t2, const Vector<VectorType, 1, VectorGroup> &vector) : data{ static_cast<Type>(t1), static_cast<Type>(t2), static_cast<Type>(vector.x()) } {}
  template<typename VectorType, VectorFlag VectorGroup, std::size_t S = Size, typename T1, std::enable_if_t<S == 3, bool> = true> constexpr Vector(const Vector<VectorType, 2, VectorGroup> &vector, T1 t1) : data{ static_cast<Type>(vector.x()), static_cast<Type>(vector.y()), static_cast<Type>(t1) } {}
  template<typename VectorType, VectorFlag VectorGroup, std::size_t S = Size, typename T1, std::enable_if_t<S == 3, bool> = true> constexpr Vector(T1 t1, const Vector<VectorType, 2, VectorGroup> &vector) : data{ static_cast<Type>(t1), static_cast<Type>(vector.x()), static_cast<Type>(vector.y()) } {}
  template<typename VectorType, VectorFlag VectorGroup, std::size_t S = Size, typename T1, typename T2, typename T3, std::enable_if_t<S == 4, bool> = true> constexpr Vector(const Vector<VectorType, 1, VectorGroup> &vector, T1 t1, T2 t2, T3 t3) : data{ static_cast<Type>(vector.x()), static_cast<Type>(t1), static_cast<Type>(t2), static_cast<Type>(t3) } {}
  template<typename VectorType, VectorFlag VectorGroup, std::size_t S = Size, typename T1, typename T2, typename T3, std::enable_if_t<S == 4, bool> = true> constexpr Vector(T1 t1, T2 t2, T3 t3, const Vector<VectorType, 1, VectorGroup> &vector) : data{ static_cast<Type>(t1), static_cast<Type>(t2), static_cast<Type>(t3), static_cast<Type>(vector.x()) } {}
  template<typename VectorType, VectorFlag VectorGroup, std::size_t S = Size, typename T1, typename T2, std::enable_if_t<S == 4, bool> = true> constexpr Vector(const Vector<VectorType, 2, VectorGroup> &vector, T1 t1, T2 t2) : data{ static_cast<Type>(vector.x()), static_cast<Type>(vector.y()), static_cast<Type>(t1), static_cast<Type>(t2) } {}
  template<typename VectorType, VectorFlag VectorGroup, std::size_t S = Size, typename T1, typename T2, std::enable_if_t<S == 4, bool> = true> constexpr Vector(T1 t1, T2 t2, const Vector<VectorType, 2, VectorGroup> &vector) : data{ static_cast<Type>(t1), static_cast<Type>(t2), static_cast<Type>(vector.x()), static_cast<Type>(vector.y()) } {}
  template<typename VectorType, VectorFlag VectorGroup, std::size_t S = Size, typename T1, std::enable_if_t<S == 4, bool> = true> constexpr Vector(const Vector<VectorType, 3, VectorGroup> &vector, T1 t1) : data{ static_cast<Type>(vector.x()), static_cast<Type>(vector.y()), static_cast<Type>(vector.z()), static_cast<Type>(t1) } {}
  template<typename VectorType, VectorFlag VectorGroup, std::size_t S = Size, typename T1, std::enable_if_t<S == 4, bool> = true> constexpr Vector(T1 t1, const Vector<VectorType, 3, VectorGroup> &vector) : data{ static_cast<Type>(t1), static_cast<Type>(vector.x()), static_cast<Type>(static_cast<Type>(vector.y())), static_cast<Type>(vector.z()) } {}

  template<typename VectorType, std::size_t VectorSize, VectorFlag VectorGroup> constexpr Vector(const Vector<VectorType, VectorSize, VectorGroup> &vector) { for(std::size_t i = 0; i < std::min(Size, VectorSize); i++) data[i] = static_cast<Type>(vector[i]); }  
  template<typename VectorType, std::size_t VectorSize, VectorFlag VectorGroup> constexpr explicit operator Vector<VectorType, VectorSize, VectorGroup>() { return Vector<VectorType, VectorSize, VectorGroup>(*this); }

  #ifdef GLM_SETUP_INCLUDED
  template<typename VectorType, glm::vec1::length_type VectorSize, glm::qualifier VectorQualifier> constexpr operator glm::vec<VectorSize, VectorType, VectorQualifier>() { return (*this).ToGlm(); }
  template<typename VectorType, glm::qualifier VectorQualifier> constexpr operator glm::qua<VectorType, VectorQualifier>() { return (*this).ToGlm(); }

  template<typename VectorType, glm::qualifier VectorQualifier> constexpr Vector(const glm::vec<1, VectorType, VectorQualifier> &vector) : data { static_cast<Type>(vector.x) } {}
  template<typename VectorType, glm::qualifier VectorQualifier, std::size_t S = Size, typename std::enable_if_t< S == 1, bool> = true> constexpr Vector(const glm::vec<2, VectorType, VectorQualifier> &vector) : data{ static_cast<Type>(vector.x) } {}
  template<typename VectorType, glm::qualifier VectorQualifier, std::size_t S = Size, typename std::enable_if_t<(S > 1), bool> = true> constexpr Vector(const glm::vec<2, VectorType, VectorQualifier> &vector) : data{ static_cast<Type>(vector.x), static_cast<Type>(vector.y) } {}
  template<typename VectorType, glm::qualifier VectorQualifier, std::size_t S = Size, typename std::enable_if_t< S == 1, bool> = true> constexpr Vector(const glm::vec<3, VectorType, VectorQualifier> &vector) : data{ static_cast<Type>(vector.x) } {}
  template<typename VectorType, glm::qualifier VectorQualifier, std::size_t S = Size, typename std::enable_if_t< S == 2, bool> = true> constexpr Vector(const glm::vec<3, VectorType, VectorQualifier> &vector) : data{ static_cast<Type>(vector.x), static_cast<Type>(vector.y) } {}
  template<typename VectorType, glm::qualifier VectorQualifier, std::size_t S = Size, typename std::enable_if_t<(S > 2), bool> = true> constexpr Vector(const glm::vec<3, VectorType, VectorQualifier> &vector) : data{ static_cast<Type>(vector.x), static_cast<Type>(vector.y), static_cast<Type>(vector.z) } {}
  template<typename VectorType, glm::qualifier VectorQualifier, std::size_t S = Size, typename std::enable_if_t< S == 1, bool> = true> constexpr Vector(const glm::vec<4, VectorType, VectorQualifier> &vector) : data{ static_cast<Type>(vector.x) } {}
  template<typename VectorType, glm::qualifier VectorQualifier, std::size_t S = Size, typename std::enable_if_t< S == 2, bool> = true> constexpr Vector(const glm::vec<4, VectorType, VectorQualifier> &vector) : data{ static_cast<Type>(vector.x), static_cast<Type>(vector.y) } {}
  template<typename VectorType, glm::qualifier VectorQualifier, std::size_t S = Size, typename std::enable_if_t< S == 3, bool> = true> constexpr Vector(const glm::vec<4, VectorType, VectorQualifier> &vector) : data{ static_cast<Type>(vector.x), static_cast<Type>(vector.y), static_cast<Type>(vector.z) } {}
  template<typename VectorType, glm::qualifier VectorQualifier, std::size_t S = Size, typename std::enable_if_t<(S > 3), bool> = true> constexpr Vector(const glm::vec<4, VectorType, VectorQualifier> &vector) : data{ static_cast<Type>(vector.x), static_cast<Type>(vector.y), static_cast<Type>(vector.z), static_cast<Type>(vector.w) } {}
  template<typename QuaternionType, glm::qualifier QuaternionQualifier, std::size_t S = Size, typename std::enable_if_t< S == 1, bool> = true> constexpr Vector(const glm::qua<QuaternionType, QuaternionQualifier> &quaternion) : data{ static_cast<Type>(quaternion.x) } {}
  template<typename QuaternionType, glm::qualifier QuaternionQualifier, std::size_t S = Size, typename std::enable_if_t< S == 2, bool> = true> constexpr Vector(const glm::qua<QuaternionType, QuaternionQualifier> &quaternion) : data{ static_cast<Type>(quaternion.x), static_cast<Type>(quaternion.y) } {}
  template<typename QuaternionType, glm::qualifier QuaternionQualifier, std::size_t S = Size, typename std::enable_if_t< S == 3, bool> = true> constexpr Vector(const glm::qua<QuaternionType, QuaternionQualifier> &quaternion) : data{ static_cast<Type>(quaternion.x), static_cast<Type>(quaternion.y), static_cast<Type>(quaternion.z) } {}
  template<typename QuaternionType, glm::qualifier QuaternionQualifier, std::size_t S = Size, typename std::enable_if_t<(S > 3), bool> = true> constexpr Vector(const glm::qua<QuaternionType, QuaternionQualifier> &quaternion) : data{ static_cast<Type>(quaternion.x), static_cast<Type>(quaternion.y), static_cast<Type>(quaternion.z), static_cast<Type>(quaternion.w) } {}
  #endif

  // Functions

  template<typename T = DefFloatType> inline constexpr T Magnitude() const { return static_cast<T>(sqrt(Dot<T>(*this, *this))); }
  template<typename T = DefFloatType> inline constexpr T SquareMagnitude() const { return Dot<T>(*this, *this); }
  template<typename T = DefFloatType, typename VectorType, std::size_t VectorSize, VectorFlag VectorGroup> inline constexpr T Dot(const Vector<VectorType, VectorSize, VectorGroup> &vector) const { return Dot(*this, vector); }
  template<typename T = DefFloatType, typename VectorType> inline constexpr Self Cross(const Vec3T<VectorType> &vector) const { return Cross(*this, vector); }
  inline constexpr Self Normalized() const;
  inline void Normalize();
  inline void ClampMagnitude(DefFloatType min, DefFloatType max) { SetMagnitude(std::min(std::max(Magnitude(), min), max)); }
  inline void SetMagnitude(DefFloatType newMagnitude) { Normalize(); for(std::size_t i = 0; i < Size; i++) data[i] *= newMagnitude; }
  #ifdef GLM_SETUP_INCLUDED
  template<typename T = Type, std::size_t S = Size, std::enable_if_t<S == 1  && !isQuaternion, bool> = true> inline constexpr glm::vec<1, T> ToGlm() const { return glm::vec<1, T>(static_cast<T>(x())); }
  template<typename T = Type, std::size_t S = Size, std::enable_if_t<S == 2  && !isQuaternion, bool> = true> inline constexpr glm::vec<2, T> ToGlm() const { return glm::vec<2, T>(static_cast<T>(x()), static_cast<T>(y())); }
  template<typename T = Type, std::size_t S = Size, std::enable_if_t<S == 3  && !isQuaternion, bool> = true> inline constexpr glm::vec<3, T> ToGlm() const { return glm::vec<3, T>(static_cast<T>(x()), static_cast<T>(y()), static_cast<T>(z())); }
  template<typename T = Type, std::size_t S = Size, std::enable_if_t<S == 4  && !isQuaternion, bool> = true> inline constexpr glm::vec<4, T> ToGlm() const { return glm::vec<4, T>(static_cast<T>(x()), static_cast<T>(y()), static_cast<T>(z()), static_cast<T>(w())); }
  template<typename T = Type, std::size_t S = Size, std::enable_if_t<(S > 4) && !isQuaternion, bool> = true> inline constexpr glm::vec<4, T> ToGlm() const { return glm::vec<1, T>(static_cast<Type>(x()), static_cast<Type>(y()), static_cast<Type>(z()), static_cast<Type>(w())); }
  template<typename T = Type, std::size_t isQ = isQuaternion, std::enable_if_t<isQ, bool> = true> inline constexpr glm::qua<T> ToGlm() const { return glm::qua<T>(static_cast<T>(w()), static_cast<T>(x()), static_cast<T>(y()), static_cast<T>(z())); }
  #endif
  
  // Acces

  inline constexpr Type &x() { return data[0]; }
  inline constexpr Type &y() { static_assert(Size > 1, "No parametr y in Vector less then 2"); return data[1]; }
  inline constexpr Type &z() { static_assert(Size > 2, "No parametr z in Vector less then 3"); return data[2]; }
  inline constexpr Type &w() { static_assert(Size > 3, "No parametr w in Vector less then 4"); return data[3]; }
  inline constexpr const Type &x() const { return data[0]; }
  inline constexpr const Type &y() const { static_assert(Size > 1, "No parametr y in Vector less then 2"); return data[1]; }
  inline constexpr const Type &z() const { static_assert(Size > 2, "No parametr z in Vector less then 3"); return data[2]; }
  inline constexpr const Type &w() const { static_assert(Size > 3, "No parametr w in Vector less then 4"); return data[3]; }
  inline constexpr Type r() { return data[0]; }
  inline constexpr Type g() { static_assert(Size > 1, "No parametr g in Vector less then 2"); return data[1]; }
  inline constexpr Type b() { static_assert(Size > 2, "No parametr b in Vector less then 3"); return data[2]; }
  inline constexpr Type a() { static_assert(Size > 3, "No parametr a in Vector less then 4"); return data[3]; }
  inline constexpr const Type &r() const { return data[0]; }
  inline constexpr const Type &g() const { static_assert(Size > 1, "No parametr g in Vector less then 2"); return data[1]; }
  inline constexpr const Type &b() const { static_assert(Size > 2, "No parametr b in Vector less then 3"); return data[2]; }
  inline constexpr const Type &a() const { static_assert(Size > 3, "No parametr a in Vector less then 4"); return data[3]; }
  inline constexpr Type &s() { return data[0]; }
  inline constexpr Type &t() { static_assert(Size > 1, "No parametr t in Vector less then 2"); return data[1]; }
  inline constexpr Type &p() { static_assert(Size > 2, "No parametr p in Vector less then 3"); return data[2]; }
  inline constexpr Type &q() { static_assert(Size > 3, "No parametr q in Vector less then 4"); return data[3]; }
  inline constexpr const Type &s() const { return data[0]; }
  inline constexpr const Type &t() const { static_assert(Size > 1, "No parametr t in Vector less then 2"); return data[1]; }
  inline constexpr const Type &p() const { static_assert(Size > 2, "No parametr p in Vector less then 3"); return data[2]; }
  inline constexpr const Type &q() const { static_assert(Size > 3, "No parametr q in Vector less then 4"); return data[3]; }

  // Performes bounds checking
  template<typename T = Type> inline constexpr const T &At(std::size_t index) const { assert((index < Size, "Too big index")); return static_cast<T>(data[index]); }
  // Performes bounds checking
  template<std::size_t Index, typename T = Type> inline constexpr const T &At() const { static_assert(Index < Size, "Too big index"); return static_cast<T>(data[Index]); }
  // Performes bounds checking
  template<typename T = Type> inline constexpr T &At(std::size_t index) { assert((index < Size, "Too big index")); return static_cast<T>(data[index]); }
  // Performes bounds checking
  template<std::size_t Index, typename T = Type> inline constexpr T &At() { static_assert(Index < Size, "Too big index"); return static_cast<T>(data[Index]); }
  
  // Just gets value
  template<std::size_t Index, typename T = Type> inline constexpr T Get() const { return static_cast<T>(data[Index]); }
  // Just gets value
  template<typename T = Type> inline constexpr T Get(std::size_t index) const { return static_cast<T>(data[index]); }

  inline Type &operator[](std::size_t index) { return data[index]; }
  inline constexpr Type operator[](std::size_t index) const { return data[index]; }

  // Both Get and At can be used to swizzle vector

  // Swizzling (kind of)

  template<typename... Args> inline constexpr Vector<Type, sizeof...(Args), Group> Get(Args... args) const;
  template<std::size_t... Indexes, typename std::enable_if_t<(sizeof...(Indexes) > 1), bool> = true> inline constexpr Vector<Type, sizeof...(Indexes), Group> Get() const;
  template<typename... Args> inline constexpr Vector<Type, sizeof...(Args), Group> At(Args... args) const;
  template<std::size_t... Indexes, typename std::enable_if_t<(sizeof...(Indexes) > 1), bool> = true> inline constexpr Vector<Type, sizeof...(Indexes), Group> At() const;


  // Quaternion Functions

  inline constexpr Self Inversed() const { static_assert(isQuaternion, "Can't inverse non quaternion"); Self result = Normalized(); return result.GetConjugate(); }
  inline Self Inverse() { static_assert(isQuaternion, "Can't inverse non quaternion"); Normalize(); data = {-x(), -y(), -z(), w()}; }
  inline constexpr Self GetConjugate() const { static_assert(isQuaternion, "Can't Get conjugate in non quaternion"); return Self(-x(), -y(), -z(), w()); }
  // Note: Angle returned in radians
  template<typename VectorType, typename T> inline void GetAxisAndAngle(Vec3T<VectorType> &axis, T &angle) const;
  template<typename T = Type> inline constexpr Vec3T<T> GetEulerAngles() const;


  // Static functions

  template<typename T = DefFloatType, typename Vector1Type, typename Vector2Type, std::size_t VectorSize, VectorFlag Vector1Group, VectorFlag Vector2Group> static constexpr inline T Dot(const Vector<Vector1Type, VectorSize, Vector1Group> &vector1, const Vector<Vector2Type, VectorSize, Vector2Group> &vector2);
  template<typename T = Type, typename Vector1Type, typename Vector2Type> static inline constexpr Vec3T<T> Cross(const Vec3T<Vector1Type> &vector1, const Vec3T<Vector2Type> &vector2);
  template<typename T = DefFloatType, typename VectorType, std::size_t VectorSize, VectorFlag VectorGroup> static inline constexpr T Magnitude(const Vector<VectorType, VectorSize, VectorGroup> &vector) { return vector.template Magnitude<T>(); }
  template<typename T = DefFloatType, typename VectorType, std::size_t VectorSize, VectorFlag VectorGroup> static inline constexpr T SquareMagnitude(const Vector<VectorType, VectorSize, VectorGroup> &vector) { return vector.template SquareMagnitude<T>(); }
  static inline constexpr const Self &Min(const Self &vector1, const Self &vector2) { return vector1.Magnitude() < vector2.Magnitude() ? vector1 : vector2; }
  static inline constexpr const Self &Max(const Self &vector1, const Self &vector2) { return vector1.Magnitude() > vector2.Magnitude() ? vector1 : vector2; }


  // Quaternion static functions

  // Input values in radians
  template<typename T = Type, typename VectorType> static inline constexpr QuaT<T> FromEuler(Vec3T<VectorType> vector) { return Self::FromEuler(static_cast<DefFloatType>(vector.x()), static_cast<DefFloatType>(vector.y()), static_cast<DefFloatType>(vector.z())); }
  // Input values in radians
  template<typename T = Type> static constexpr QuaT<T> FromEuler(DefFloatType pitch = 0, DefFloatType yaw = 0, DefFloatType roll = 0);
  // Input values in radians
  template<typename VectorType, typename T = Type> static constexpr QuaT<T> FromAxis(Vec3T<VectorType> vector, DefFloatType angle);


  // Operators

  template<typename VectorType, std::size_t VectorSize, VectorFlag VectorGroup> friend inline constexpr std::ostream &operator<<(const std::ostream &stream, const Vector<VectorType, VectorSize, VectorGroup> &self);
  inline constexpr Self operator-() const;

  template<typename VectorType, std::size_t VectorSize, VectorFlag VectorGroup> inline constexpr std::conditional_t<(VectorSize > Size), Vector<VectorType, VectorSize, VectorGroup>, Self> operator+(const Vector<VectorType, VectorSize, VectorGroup> &vector) const;
  template<typename T> inline constexpr Self operator+(T value) const;
  template<typename VectorType, std::size_t VectorSize, VectorFlag VectorGroup> inline constexpr std::conditional_t<(VectorSize > Size), Vector<VectorType, VectorSize, VectorGroup>, Self> operator-(const Vector<VectorType, VectorSize, VectorGroup> &vector) const;
  template<typename T> inline constexpr Self operator-(T value) const;
  template<typename VectorType, std::size_t VectorSize, VectorFlag VectorGroup> inline constexpr std::conditional_t<(VectorSize > Size), Vector<VectorType, VectorSize, VectorGroup>, Self> operator*(const Vector<VectorType, VectorSize, VectorGroup> &vector) const;
  template<typename T> inline constexpr Self operator*(T value) const;
  template<typename VectorType, std::size_t VectorSize, VectorFlag VectorGroup> inline constexpr std::conditional_t<(VectorSize > Size), Vector<VectorType, VectorSize, VectorGroup>, Self> operator/(const Vector<VectorType, VectorSize, VectorGroup> &vector) const;
  template<typename T> inline constexpr Self operator/(T value) const;

  template<typename QuaternionType, bool IsQ = isQuaternion, typename std::enable_if_t<IsQ, bool> = true> inline constexpr QuaT<QuaternionType> operator*(const QuaT<QuaternionType> &quaternion) const;
  template<typename VectorType, bool IsQ = isQuaternion, typename std::enable_if_t<IsQ, bool> = true> inline constexpr Vec3T<VectorType> operator*(Vec3T<VectorType> vector) const;
  template<typename QuaternionType, bool IsQ = isQuaternion, typename std::enable_if_t<!IsQ, bool> = true> inline constexpr operator*(const QuaT<QuaternionType> &quaternion) const { return quaternion * (*this); }


  // Constants

  static inline constexpr Self zero() { return Self(); }
  static inline constexpr Self one() { return Self(1); }
};

template<typename T, std::enable_if_t<!IsVectorClass<T>, bool> = true, typename VectorType, std::size_t VectorSize, VectorFlag VectorGroup> inline constexpr Vector<VectorType, VectorSize, VectorGroup> operator+(const T &value, const Vector<VectorType, VectorSize, VectorGroup> &vector) { return vector + value; }
template<typename T, std::enable_if_t<!IsVectorClass<T>, bool> = true, typename VectorType, std::size_t VectorSize, VectorFlag VectorGroup> inline constexpr Vector<VectorType, VectorSize, VectorGroup> operator*(const T &value, const Vector<VectorType, VectorSize, VectorGroup> &vector) { return vector * value; }
}

#endif

#include "Math/Vector.tpp"