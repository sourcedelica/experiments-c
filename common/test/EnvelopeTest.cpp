#include "../Envelope.h"
#include "catch.hpp"

TEST_CASE("Envelope Serialization", "[Envelope][Protobuf][unit]") {
    Envelope envelope(42, 100, 1, true);
    std::string serialized;
    envelope.serialize(&serialized);

    Envelope output;
    output.deserialize(serialized.data(), static_cast<int>(serialized.size()));

    REQUIRE(output == envelope);
}
