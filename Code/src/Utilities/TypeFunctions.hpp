#ifndef TYPE_FUNCTIONS_HPP
#define TYPE_FUNCTIONS_HPP

#include <type_traits>

namespace Tolik
{
template<bool Condition> struct Warning{};
template<> struct __attribute__((deprecated)) Warning<false> { constexpr Warning() {} };
#define StaticWarn(x, ...) ((void) Warning<x>())

template<typename... Args> struct Identity {};
struct Empty { template<typename... Args> constexpr Empty(const Args&... args) {} };

template<std::size_t Num, typename... Null> struct GetTypeInPlace;
template<std::size_t Num, typename T> struct GetTypeInPlace<Num, T>
{ using type = std::conditional_t<Num == 0, T, void>; };
template<std::size_t Num, typename T, typename... Types> struct GetTypeInPlace<Num, T, Types...>
{ using type = std::conditional_t<Num == 0, T, typename GetTypeInPlace<Num - 1, Types...>::type>; };
template<std::size_t Num, typename... Args> using HelperGetTypeInPlace = typename GetTypeInPlace<Num, Args...>::type;

// Causes error with MinGW 13 where it can't find defenition of operator != between std::pair
/*
enum class OperatorType : uint8_t
{
	Equals, LessThen, MoreThen, NotEquals
};

template<OperatorType Operator, typename Type1, typename Type2 = Type1> struct HasOperator { enum { value = false }; };

#define OPERATOR_CHECK_DEFENITION(oper, operatorType)  \
template<typename Type1, typename Type2> inline constexpr Empty operator oper (const Type1 &value1, const Type2 &value2); \
template<typename Type1, typename Type2> struct HasOperator<operatorType, Type1, Type2> \
: std::bool_constant<!std::is_same_v<decltype(std::declval<Type1>() oper std::declval<Type2>()), Empty>> {}

OPERATOR_CHECK_DEFENITION(==, OperatorType::Equals);
OPERATOR_CHECK_DEFENITION(!=, OperatorType::NotEquals);
OPERATOR_CHECK_DEFENITION(<, OperatorType::LessThen);
OPERATOR_CHECK_DEFENITION(>, OperatorType::MoreThen);
template<OperatorType Operator, typename Type1, typename Type2 = Type1> inline constexpr bool HelperHasOperator = HasOperator<Operator, Type1, Type2>::value;
*/
}

#endif