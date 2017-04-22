#include "../Registration.h"
#include "catch.hpp"

TEST_CASE("Registration Serialization", "[Registration][Protobuf][unit]") {
    Registration registration(Registration::Unregister, 42, "fred");
    std::string serialized;
    registration.serialize(&serialized);

    Registration output;
    output.deserialize(serialized.c_str(), static_cast<int>(serialized.size()));

    REQUIRE(output == registration);
}
