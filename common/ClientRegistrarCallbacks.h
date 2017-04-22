#pragma once

#include <functional>

struct ClientRegistrarCallbacks {
    std::function<void(int)> onClientConnected;
    std::function<void(int)> onClientDisconnected;
};
