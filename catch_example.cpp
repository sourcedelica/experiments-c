#include "catch_tests.h"
#include <iostream>

TEST_CASE("This is a test", "[example]") {
    std::cout << CatchTests::currentTestCaseName << std::endl;

    SECTION("First section") {
        std::cout << CatchTests::currentSectionName << std::endl;
    }

    SECTION("Second section") {
        std::cout << CatchTests::currentSectionName << std::endl;
    }
}

