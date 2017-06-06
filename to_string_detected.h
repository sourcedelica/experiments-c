#pragma once

#include "is_detected.h"
#include <string>
#include <sstream>

namespace detail {
    template<typename T>
    using std_to_string_expression = decltype(std::to_string(std::declval<T>()));

    template<typename T>
    constexpr bool has_std_to_string = is_detected<std_to_string_expression, T>;


    template<typename T>
    using non_member_to_string_expression = decltype(to_string(std::declval<T>()));

    template<typename T>
    constexpr bool has_non_member_to_string = is_detected<non_member_to_string_expression, T>;


    template<typename T>
    using member_to_string_expression = decltype(std::declval<T&>().to_string());

    template<typename T>
    constexpr bool has_member_to_string = is_detected<member_to_string_expression, T>;


    template<typename T>
    using ostringstream_expression = decltype(std::declval<std::ostringstream &>() << std::declval<T>());

    template<typename T>
    constexpr bool has_ostringstream = is_detected<ostringstream_expression, T>;
}

// Converts toString(const T&) to std::to_string(const T&)
template<
    typename T,
    typename std::enable_if<detail::has_std_to_string<T>, int>::type = 0
>
std::string toString(T const& t) {
    return std::to_string(t);
}

// Converts toString(const T&) -> non-member to_string(const T&) -> std::string
template<
    typename T,
    typename std::enable_if<!detail::has_std_to_string<T> && detail::has_non_member_to_string<T>, int>::type = 0
>
std::string toString(T const& t) {
    return to_string(t);
}

// Converts toString(const T& t) -> t.to_string() -> std::string
template<
    typename T,
    typename std::enable_if<detail::has_member_to_string<T>, int>::type = 0
>
std::string toString(T const& t) {
    return t.to_string();
}

// Converts toString(const T& t) -> ostringstream << t -> std::string
template<
    typename T,
    typename std::enable_if<!detail::has_std_to_string<T> && !detail::has_non_member_to_string<T> &&
                            !detail::has_member_to_string<T> && detail::has_ostringstream<T>, int>::type = 0
>
std::string toString(T const& t) {
    std::ostringstream oss;
    oss << t;
    return oss.str();
}
