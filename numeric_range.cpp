#include "numeric_range.h"
#include <iostream>

int main() {
    for (int x: range(10)) {
        std::cout << x << ",";
    }
    std::cout << std::endl;
    for (int x: range(0)) {
        std::cout << x << ",";
    }
    std::cout << std::endl;
    for (int x: range(1, 11)) {
        std::cout << x << ",";
    }
    std::cout << std::endl;
    for (int x: range(0, 30, 5)) {
        std::cout << x << ",";
    }
    std::cout << std::endl;
    for (int x: range(0, -10, -1)) {
        std::cout << x << ",";
    }
    std::cout << std::endl;
    for (int x: range(0, 31, 5)) {
        std::cout << x << ",";
    }
    std::cout << std::endl;
    for (int x: range(0, 10, 3)) {
        std::cout << x << ",";
    }
    std::cout << std::endl;
    for (double x: range(0.1, 30.1)) {
        std::cout << x << ",";
    }
    std::cout << std::endl;
    for (double x: range(0.1, 1.1, 0.1)) {
        std::cout << x << ",";
    }
    std::cout << std::endl;
    auto myrange = range(5);
    for (auto it = myrange.begin(); it != myrange.end();) {
        std::cout << *it++ << ",";
    }
    std::cout << std::endl;
}
