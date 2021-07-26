#include "catch_tests.h"
#include <iostream>

TEST_CASE("Testing", "[example][testing") {
    std::cout << CatchTests::currentTestCaseName << std::endl;

    SECTION("First section") {
        std::cout << CatchTests::currentSectionName << std::endl;
    }

    SECTION("Second section") {
        std::cout << CatchTests::currentSectionName << std::endl;
    }
}

TEST_CASE("This is a test", "[example][foo bar]") {
    std::cout << CatchTests::currentTestCaseName << std::endl;

    SECTION("First section") {
        std::cout << CatchTests::currentSectionName << std::endl;
    }

    SECTION("Second section") {
        std::cout << CatchTests::currentSectionName << std::endl;
    }
}

TEST_CASE("Another test", "[example][baz bip]") {
    std::cout << CatchTests::currentTestCaseName << std::endl;

    SECTION("First section") {
        std::cout << CatchTests::currentSectionName << std::endl;
    }

    SECTION("Second section") {
        std::cout << CatchTests::currentSectionName << std::endl;
    }
}
