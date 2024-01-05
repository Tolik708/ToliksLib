#ifndef TOLIK_MATH_UTILS_HPP
#define TOLIK_MATH_UTILS_HPP

#include <type_traits>

#include "Tolik/Setup.hpp"

#include "Tolik/Math/Constants.hpp"

namespace Tolik
{
template<typename T> constexpr std::conditional_t<std::is_integral_v<T>, DefFloatType, T> DegreesToRadians(T degrees)
{ static_assert(std::is_arithmetic_v<T>, "Can't convert non arithmetic type to radians"); return degrees * (Constants::PI / 180); }
template<typename T> constexpr std::conditional_t<std::is_integral_v<T>, DefFloatType, T> RadiansToDegrees(T radians)
{ static_assert(std::is_arithmetic_v<T>, "Can't convert non arithmetic type to degrees"); return radians * (180 / Constants::PI); }
}

#endif