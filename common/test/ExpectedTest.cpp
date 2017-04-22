#include <map>
#include "common/Expected.h"
#include "catch.hpp"

namespace {
    template <typename T>
    Expected<T> sendRecv(int clientId, const T &value) {
        return Expected<T>(value);
    }

    template <typename T>
    Expected<T> sendSync(int clientId, const T &value) {
        Expected<T> result = clientId == -1 ? Error(Error::Code::ClientInitialization)
                                            : sendRecv(clientId, value);
        return result;
    }
}

TEST_CASE("Expected RVO", "[Expected]") {
    std::map<int, std::string> map;
    map[1] = "hey";
    auto res = sendSync(1, map);
    REQUIRE(res);
    REQUIRE(res.value() == map);
}
