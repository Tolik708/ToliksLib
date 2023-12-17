#ifndef VECTOR_TPP
#define VECTOR_TPP

#include <type_traits>
#include <limits>
#include <math.h>
#include <iostream>

namespace Tolik
{
namespace Detail
{
  // Min and Max
  template<typename Type, std::size_t Size, VectorFlag Group, bool IsArithmetic> inline constexpr Vector<Type, Size, Group> MinMaxConstants<Type, Size, Group, IsArithmetic>::min() { return Vector<Type, Size, Group>(std::numeric_limits<Type>::min()); }
  template<typename Type, std::size_t Size, VectorFlag Group, bool IsArithmetic> inline constexpr Vector<Type, Size, Group> MinMaxConstants<Type, Size, Group, IsArithmetic>::max() { return Vector<Type, Size, Group>(std::numeric_limits<Type>::max()); }
  
  // Vector
  template<typename Type, std::size_t Size> inline constexpr Vector<Type, Size, VectorFlag::Vector> DirectionalConstants<Type, Size, 1>::right()    { return Vector<Type, Size, VectorFlag::Vector>(Identity<NonScalar>(), 1); }
  template<typename Type, std::size_t Size> inline constexpr Vector<Type, Size, VectorFlag::Vector> DirectionalConstants<Type, Size, 1>::left()     { return Vector<Type, Size, VectorFlag::Vector>(Identity<NonScalar>(), -1); }
  template<typename Type, std::size_t Size> inline constexpr Vector<Type, Size, VectorFlag::Vector> DirectionalConstants<Type, Size, 2>::up()       { return Vector<Type, Size, VectorFlag::Vector>(0, 1); }
  template<typename Type, std::size_t Size> inline constexpr Vector<Type, Size, VectorFlag::Vector> DirectionalConstants<Type, Size, 2>::down()     { return Vector<Type, Size, VectorFlag::Vector>(0, -1); }
  template<typename Type, std::size_t Size> inline constexpr Vector<Type, Size, VectorFlag::Vector> DirectionalConstants<Type, Size, 3>::backward() { return Vector<Type, Size, VectorFlag::Vector>(0, 0, 1); }
  template<typename Type, std::size_t Size> inline constexpr Vector<Type, Size, VectorFlag::Vector> DirectionalConstants<Type, Size, 3>::forward()  { return Vector<Type, Size, VectorFlag::Vector>(0, 0, -1); }

  // Quaternion
  template<typename Type> inline constexpr QuaT<Type> VectorConstants<Type, 4, VectorFlag::Quaternion>::identity() { return QuaT<Type>(0, 0, 0, 1); }

  // Color24
  inline constexpr Color24 VectorConstants<uint8_t, 3, VectorFlag::Color>::black() { return Color24(); }
  inline constexpr Color24 VectorConstants<uint8_t, 3, VectorFlag::Color>::white() { return Color24(255, 255, 255); }

  // Color32
  inline constexpr Color32 VectorConstants<uint8_t, 4, VectorFlag::Color>::black() { return Color32(0, 0, 0, 255); }
  inline constexpr Color32 VectorConstants<uint8_t, 4, VectorFlag::Color>::white() { return Color32(255, 255, 255, 255); }

  // UnitColor
  inline constexpr UnitColor VectorConstants<DefFloatType, 4, VectorFlag::Color>::black() { return UnitColor(0, 0, 0, 1); }
  inline constexpr UnitColor VectorConstants<DefFloatType, 4, VectorFlag::Color>::white() { return UnitColor(1, 1, 1, 1); }
}

// Functions

template<typename Type, std::size_t Size, VectorFlag Group>
inline constexpr Vector<Type, Size, Group> Vector<Type, Size, Group>::Normalized() const
{
  DefFloatType magnitude = SquareMagnitude();
  if(magnitude == 0)
    return Self();

  magnitude = 1 / sqrt(magnitude);

  Self result;
  for(std::size_t i = 0; i < Size; i++)
    result[i] = data[i] * magnitude;

  return result;
}

template<typename Type, std::size_t Size, VectorFlag Group>
inline void Vector<Type, Size, Group>::Normalize()
{ 
  Type magnitude = Magnitude();
  if(magnitude == 0)
    return;

  magnitude = 1 / magnitude;

  for(std::size_t i = 0; i < Size; i++)
    data[i] *= magnitude;
}

template<typename Type, std::size_t Size, VectorFlag Group>
template<typename... Args>
inline constexpr Vector<Type, sizeof...(Args), Group> Vector<Type, Size, Group>::Get(Args... args) const
{
  static_assert(std::conjunction_v<std::is_convertible_v<Args, std::size_t>...>, "Can't convert IndexType to std::size_t");
  return Vector<Type, sizeof...(Args), Group>((data[static_cast<std::size_t>(args)], ...));
}

template<typename Type, std::size_t Size, VectorFlag Group>
template<std::size_t... Indexes, typename std::enable_if_t<(sizeof...(Indexes) > 1), bool>>
inline constexpr Vector<Type, sizeof...(Indexes), Group> Vector<Type, Size, Group>::Get() const
{
  return Vector<Type, sizeof...(Indexes), Group>((data[Indexes], ...));
}

template<typename Type, std::size_t Size, VectorFlag Group>
template<typename... Args>
inline constexpr Vector<Type, sizeof...(Args), Group> Vector<Type, Size, Group>::At(Args... args) const
{
  static_assert(std::conjunction_v<std::is_convertible_v<Args, std::size_t>...>, "Can't convert Index to std::size_t");
  assert(("Too big index", ((args < Size) || ...)));
  return Vector<Type, sizeof...(Args), Group>((data[static_cast<std::size_t>(args)], ...));
}

template<typename Type, std::size_t Size, VectorFlag Group>
template<std::size_t... Indexes, typename std::enable_if_t<(sizeof...(Indexes) > 1), bool>>
inline constexpr Vector<Type, sizeof...(Indexes), Group> Vector<Type, Size, Group>::At() const
{
  static_assert(std::conjunction_v<std::bool_constant<(Indexes < Size)>...>, "Too big index");
  return Vector<Type, sizeof...(Indexes), Group>((data[Indexes], ...));
}


template<typename Type, std::size_t Size, VectorFlag Group>
template<typename T, typename Vector1Type, typename Vector2Type, std::size_t VectorSize, VectorFlag Vector1Group, VectorFlag Vector2Group>
inline constexpr T Vector<Type, Size, Group>::Dot(const Vector<Vector1Type, VectorSize, Vector1Group> &vector1, const Vector<Vector2Type, VectorSize, Vector2Group> &vector2)
{
  T result = 0;
  for(std::size_t i = 0; i < Size; i++)
    result = result + static_cast<T>(vector1[i] * vector2[i]);
  return result;
}

template<typename Type, std::size_t Size, VectorFlag Group>
template<typename T, typename Vector1Type, typename Vector2Type>
inline constexpr Vec3T<T> Vector<Type, Size, Group>::Cross(const Vec3T<Vector1Type> &vector1, const Vec3T<Vector2Type> &vector2)
{
  static_assert(Size == 3, "Can't call cross product on non 3d vectors");
  return Vec3T<T>(static_cast<T>(vector1.template Get<1>() * vector2.template Get<2>() - vector1.template Get<2>() * vector2.template Get<1>()),
                  static_cast<T>(vector1.template Get<2>() * vector2.template Get<0>() - vector1.template Get<0>() * vector2.template Get<2>()),
                  static_cast<T>(vector1.template Get<0>() * vector2.template Get<1>() - vector1.template Get<1>() * vector2.template Get<0>()));
}

template<typename Type, std::size_t Size, VectorFlag Group>
template<typename VectorType, typename T>
inline constexpr QuaT<T> Vector<Type, Size, Group>::FromAxis(Vec3T<VectorType> vector, DefFloatType angle)
{
  angle *= 0.5;
  DefFloatType sinAngle = sin(angle);
  return QuaT<T>(static_cast<T>(vector.template Get<0>() * sinAngle),
                 static_cast<T>(vector.template Get<1>() * sinAngle),
                 static_cast<T>(vector.template Get<2>() * sinAngle),
                 static_cast<T>(cos(angle)));
}

template<typename Type, std::size_t Size, VectorFlag Group>
template<typename T>
inline constexpr QuaT<T> Vector<Type, Size, Group>::FromEuler(DefFloatType pitch, DefFloatType yaw, DefFloatType roll)
{
  pitch /= 2;
  yaw /= 2;
  roll /= 2;
  DefFloatType cosPitch = cos(pitch);
  DefFloatType cosYaw =   cos(yaw);
  DefFloatType cosRoll =  cos(roll);
  pitch = sin(pitch);
  yaw =   sin(yaw);
  roll =  sin(roll);
  return QuaT<T> (static_cast<T>(pitch)    * static_cast<T>(cosYaw) * static_cast<T>(cosRoll) - static_cast<T>(cosPitch) * static_cast<T>(yaw)    * static_cast<T>(roll),
                  static_cast<T>(cosPitch) * static_cast<T>(yaw)    * static_cast<T>(cosRoll) + static_cast<T>(pitch)    * static_cast<T>(cosYaw) * static_cast<T>(roll),
                  static_cast<T>(cosPitch) * static_cast<T>(cosYaw) * static_cast<T>(roll)    - static_cast<T>(pitch)    * static_cast<T>(yaw)    * static_cast<T>(cosRoll),
                  static_cast<T>(cosPitch) * static_cast<T>(cosYaw) * static_cast<T>(cosRoll) + static_cast<T>(pitch)    * static_cast<T>(yaw)    * static_cast<T>(roll));
}

template<typename Type, std::size_t Size, VectorFlag Group>
template<typename VectorType, typename T>
inline void Vector<Type, Size, Group>::GetAxisAndAngle(Vec3T<VectorType> &axis, T &angle) const
{
  DefFloatType scale = sqrt(static_cast<DefFloatType>(1 - Get<3>() * Get<3>()));
  if(scale == 0)
    axis.array = { 1, 0, 0 };
  else
    axis.array = { Get<0, VectorType>() / scale, Get<0, VectorType>() / scale, Get<0, VectorType>() / scale };
  
  angle = static_cast<T>(acos(static_cast<DefFloatType>(Get<3>())) * 2);
}

template <typename Type, std::size_t Size, VectorFlag Group>
template <typename T>
inline constexpr Vec3T<T> Vector<Type, Size, Group>::GetEulerAngles() const
{
  return Vec3T<T>(
    atan2(2 * (Get<3>() * Get<0>() + Get<1>() * Get<2>()), 1 - 2 * (Get<0>() * Get<0>() + Get<1>() * Get<1>())),
    2 * atan2(sqrt(1 + 2 * (Get<3>() * Get<1>() - Get<0>() * Get<2>())), sqrt(1 - 2 * ( Get<3>() * Get<1>() - Get<0>() * Get<2>()))) - (Constants::PI / 2),
    atan2(2 * (Get<3>() * Get<2>() + Get<1>() * Get<0>()), 1 - 2 * ( Get<1>() * Get<1>() + Get<2>() * Get<2>()))
  );
}

// Operators

template<typename VectorType, std::size_t VectorSize, VectorFlag VectorGroup>
inline constexpr std::ostream &operator<<(std::ostream &stream, const Vector<VectorType, VectorSize, VectorGroup> &self)
{
  if constexpr (VectorGroup == VectorFlag::Vector)
    stream << "Vector " << VectorSize << ':';
  else if(std::is_same_v<Vector<VectorType, VectorSize, VectorGroup>, Color24>)
    stream << "Color24: ";
  else if(std::is_same_v<Vector<VectorType, VectorSize, VectorGroup>, Color32>)
    stream << "Color32: ";
  else if(std::is_same_v<Vector<VectorType, VectorSize, VectorGroup>, UnitColor>)
    stream << "UnitColor: ";
  else if(VectorGroup == VectorFlag::Color)
    stream << "Color: ";
  else
    stream << "Quaternion: ";

  for(std::size_t i = 0; i < VectorSize; i++)
    stream << ' ' << self[i];

  return stream;
}

template<typename Type, std::size_t Size, VectorFlag Group>
inline constexpr Vector<Type, Size, Group> Vector<Type, Size, Group>::operator-() const
{
  Self result(*this);
  for(std::size_t i = 0; i < Size; i++)
    result[i] = -result[i];

  return result;
}

template<typename Type, std::size_t Size, VectorFlag Group>
template<typename QuaternionType, bool IsQ, typename std::enable_if_t<IsQ, bool>>
inline constexpr QuaT<QuaternionType> Vector<Type, Size, Group>::operator*(const QuaT<QuaternionType> &quaternion) const
{
  return QuaT<Type>(Get<0>() * quaternion.template Get<3, Type>() + Get<3>() * quaternion.template Get<0, Type>() + Get<2>() * quaternion.template Get<1, Type>() - Get<1>() * quaternion.template Get<2, Type>(),
                    Get<1>() * quaternion.template Get<3, Type>() - Get<2>() * quaternion.template Get<0, Type>() + Get<3>() * quaternion.template Get<1, Type>() + Get<0>() * quaternion.template Get<2, Type>(),
                    Get<2>() * quaternion.template Get<3, Type>() + Get<1>() * quaternion.template Get<0, Type>() - Get<0>() * quaternion.template Get<1, Type>() + Get<3>() * quaternion.template Get<2, Type>(),
                    Get<3>() * quaternion.template Get<3, Type>() - Get<0>() * quaternion.template Get<0, Type>() - Get<1>() * quaternion.template Get<1, Type>() - Get<2>() * quaternion.template Get<2, Type>());
}

template <typename Type, std::size_t Size, VectorFlag Group>
template <typename VectorType, bool IsQ, typename std::enable_if_t<IsQ, bool>>
inline constexpr Vec3T<VectorType> Vector<Type, Size, Group>::operator*(Vec3T<VectorType> vector) const
{
  QuaT<Type> result = (*this) * (QuaT<Type>(vector.template Get<0>(), vector.template Get<1>(), vector.template Get<2>()) * GetConjugate());
  return Vec3T<VectorType>(result.template Get<0>(), result.template Get<1>(), result.template Get<2>());
}

#define VECTOR_OPERATOR_DEFENITION(oper) \
template<typename Type, std::size_t Size, VectorFlag Group> \
template<typename VectorType, std::size_t VectorSize, VectorFlag VectorGroup> \
inline constexpr std::conditional_t<(VectorSize > Size), Vector<VectorType, VectorSize, VectorGroup>, Vector<Type, Size, Group>> Vector<Type, Size, Group>::operator oper (const Vector<VectorType, VectorSize, VectorGroup> &vector) const \
{ \
  std::conditional_t<(VectorSize > Size), Vector<VectorType, VectorSize, VectorGroup>, Self> result; \
  using ResultType = std::conditional_t<(VectorSize > Size), VectorType, Type>; \
  for(std::size_t i = 0; i < std::min(VectorSize, Size); i++) \
    result[i] = Get<ResultType>(i) oper vector.template Get<ResultType>(i); \
  return result; \
} \
 \
template<typename Type, std::size_t Size, VectorFlag Group> \
template<typename T> \
inline constexpr Vector<Type, Size, Group> Vector<Type, Size, Group>::operator oper (T t) const \
{ \
  Self result(*this); \
  for(std::size_t i = 0; i < Size; i++) \
    result[i] = result[i] oper static_cast<Type>(t); \
  return result; \
}

VECTOR_OPERATOR_DEFENITION(+);
VECTOR_OPERATOR_DEFENITION(-);
VECTOR_OPERATOR_DEFENITION(*);
VECTOR_OPERATOR_DEFENITION(/);

#undef VECTOR_OPERATOR_DEFENITION
}

#endif