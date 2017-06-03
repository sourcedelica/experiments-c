#include <iostream>

// Adapted from http://www.fluentcpp.com/2017/06/02/write-template-metaprogramming-expressively/
// Also see http://en.cppreference.com/w/cpp/experimental/is_detected

template <typename...>
using void_t = void;

template <template <typename...> class Expression, typename Attempt, typename... Ts>
struct is_detected_impl : std::false_type{};

template <template <typename...> class Expression, typename... Ts>
struct is_detected_impl<Expression, void_t<Expression<Ts...>>, Ts...> : std::true_type{};

template <template <typename...> class Expression, typename... Ts>
constexpr bool is_detected = is_detected_impl<Expression, void, Ts...>::value;


template <typename T, typename U>
using assignable_expression = decltype(std::declval<T&>() = std::declval<const U&>());

template <typename T, typename U>
constexpr bool is_assignable = is_detected<assignable_expression, T, U>;

struct Foo { void print() {}; };
struct Bar { void baz() {}; };

template <typename T>
using has_print_expression = decltype(std::declval<T&>().print());

template <typename T>
constexpr bool has_print = is_detected<has_print_expression, T>;


int main() {
    static_assert(is_assignable<int, char>, "char can be assigned to int");
    static_assert(!is_assignable<int, std::string>, "std::string cannot be assigned to int");
    static_assert(has_print<Foo>, "Foo has a print method");
    static_assert(!has_print<Bar>, "Bar does not have a print method");

    std::cout << "char can be assigned to int? " << std::boolalpha << is_assignable<int, char> << std::endl;
    std::cout << "std::string can be assigned to int? " << std::boolalpha << is_assignable<int, std::string> << std::endl;
    std::cout << "Foo has a print method? " << std::boolalpha << has_print<Foo> << std::endl;
    std::cout << "Bar has a print method? " << std::boolalpha << has_print<Bar> << std::endl;
};