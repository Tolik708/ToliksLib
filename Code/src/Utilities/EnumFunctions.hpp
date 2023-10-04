#ifndef ENUM_FUNCTIONS_HPP
#define ENUM_FUNCTIONS_HPP

#include <type_traits>
#include <iostream>

#define BIT(x) (1 << x)

namespace Tolik
{
template<typename T> inline std::conditional_t<std::is_enum_v<T>, std::underlying_type_t<T>, T> ToUnderlying(T value)
{
  static_assert(std::is_enum_v<T> || std::is_arithmetic_v<T>, "Can't cast non enum and non arithmetic value to underlying type");
  if constexpr(std::is_enum_v<T>)
    return static_cast<std::underlying_type_t<T>>(value);
  else
    return value;
}

template<typename T, typename U> inline T operator|(T value1, U value2) 
{return static_cast<T>(ToUnderlying(value1) | ToUnderlying(value2)); }
template<typename T, typename U> inline T operator&(T value1, U value2) 
{ return static_cast<T>(ToUnderlying(value1) & ToUnderlying(value2)); }
template<typename T, typename U> inline T operator^(T value1, U value2) 
{ return static_cast<T>(ToUnderlying(value1) ^ ToUnderlying(value2)); }
template<typename T, typename std::enable_if_t<std::is_enum_v<T>, bool> = true> inline std::ostream& operator<<(std::ostream& os, T self)
{ return os << ToUnderlying(self); }
}

#endif