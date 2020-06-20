#include "main.h"
#include <thread>
#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

bool waitForChange(std::function<bool()> predicate, int tries, int sleepMs) {
    while (!predicate() && tries) {
        std::this_thread::sleep_for(std::chrono::milliseconds(sleepMs));
        tries -= 1;
    }
    return predicate();
}

bool waitForNoChange(std::function<bool()> predicate, int tries, int sleepMs) {
    while (predicate() && tries) {
        std::this_thread::sleep_for(std::chrono::milliseconds(sleepMs));
        tries -= 1;
    }
    return predicate();
}