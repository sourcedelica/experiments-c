#include "spdlog/spdlog.h"
#include <iostream>

int main() {
    std::cout << fmt::format("Hello, {}!\n", "world");
    return 0;
}
