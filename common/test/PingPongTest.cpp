#include "common/PingPong.h"
#include "catch.hpp"

TEST_CASE("PingPong Serialization", "[PingPong][Protobuf][unit]") {
    PingPong pingPong(PingPong::Pong);
    std::string serialized;
    pingPong.serialize(&serialized);

    PingPong output(serialized.c_str(), static_cast<int>(serialized.size()));

    REQUIRE(output == pingPong);
}
