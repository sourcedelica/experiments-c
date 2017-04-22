#include "catch.hpp"
#include "../ScopedThread.h"
#include "main.h"
#include <iostream>

namespace {
    std::atomic_bool flag;

    void func(int a, int b) {
        flag = (a + b == 5);
    }
}

TEST_CASE("Constructor", "[ScopedThread]") {
    flag = false;
    auto st = ScopedThread(std::thread(func, 2, 3));

    REQUIRE((waitForChange([] { return flag.load(); })));
}

TEST_CASE("makeScopedThread", "[ScopedThread]") {
    flag = false;
    auto st = makeScopedThread(func, 2, 3);

    REQUIRE((waitForChange([] { return flag.load(); })));
}

