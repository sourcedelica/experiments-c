#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include <iostream>

TEST_CASE("This is another test", "[another][this is]") {
}

TEST_CASE("Yet another test", "[another][yet another]") {
}
