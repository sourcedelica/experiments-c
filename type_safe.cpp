#include <iostream>
#include <string>
#include "type_safe/optional.hpp"
#include "type_safe/variant.hpp"

namespace ts = type_safe;

struct my_module
    : debug_assert::default_handler, // use the default handler
      debug_assert::set_level<5>     // level 0 would mean none, 1 would be level 1, 2 level 2 or lower,...
{};

struct Foo {
    Foo() { std::cout << "Foo default ctor" << std::endl; }
};

struct Bar {
    Bar() { std::cout << "Bar default ctor" << std::endl; }
};

ts::optional<int> foo(int i) {
    return i > 0 ? i * 2 : ts::optional<int>();
}

int main() {
    auto pos = foo(2);
    DEBUG_ASSERT(pos, my_module{});

    auto plusOne = pos.map([](const int i){ return i + 1; });
    std::cout << plusOne.value_or(99) << "\n";

    auto neg = foo(-1);
    std::cout << neg.value_or(99) << "\n";

//    DEBUG_ASSERT(neg, my_module{});

    ts::variant<int, std::string, double> bv{std::string{"hey"}};

    ts::with(bv, [](int) { DEBUG_ASSERT(false, my_module{}); });
    ts::with(bv, [](std::string s) { std::cout << s << std::endl; });
    ts::with(bv, [](double) { DEBUG_ASSERT(false, my_module{}); });

    ts::basic_variant<ts::optional_variant_policy, Foo, Bar> empty;

}
