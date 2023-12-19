#ifndef MATH_FUNCTIONS_HPP
#define MATH_FUNCTIONS_HPP

#include <type_traits>

#include "Math/Constants.hpp"
#include "Utilities/TypeFunctions.hpp"

namespace Tolik
{
template<typename T> constexpr std::conditional_t<std::is_integral_v<T>, DefFloatType, T> DegreesToRadians(T degrees)
{ static_assert(std::is_arithmetic_v<T>, "Can't convert non arithmetic type to radians"); return degrees * (Constants::PI / 180); }
template<typename T> constexpr std::conditional_t<std::is_integral_v<T>, DefFloatType, T> RadiansToDegrees(T radians)
{ static_assert(std::is_arithmetic_v<T>, "Can't convert non arithmetic type to degrees"); return radians * (180 / Constants::PI); }
}

#endif