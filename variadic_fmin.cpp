#include <cmath>
#include <algorithm>
#include <initializer_list>
#include <iostream>

template <typename First, typename ...Rest>
auto variadic_fmin(const First& first, const Rest& ...rest) {
    First ret = first;

    auto list = {(ret = fmin(ret, rest))...};

    return *(list.end() - 1);
};

int main(int argc, char **argv) {
    std::cout << variadic_fmin(5.0, NAN, NAN, 3.5, NAN, 1) << std::endl;
}
