#pragma once

template <typename...>
using void_t = void;

template <template <typename...> class Expression, typename Attempt, typename... Ts>
struct is_detected_impl : std::false_type{};

template <template <typename...> class Expression, typename... Ts>
struct is_detected_impl<Expression, void_t<Expression<Ts...>>, Ts...> : std::true_type{};

template <template <typename...> class Expression, typename... Ts>
constexpr bool is_detected = is_detected_impl<Expression, void, Ts...>::value;