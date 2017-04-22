#pragma once

#include <string>

struct PingPong {
    enum Type { Ping, Pong };

    PingPong() {}
    PingPong(Type type) : type(type) {}
    PingPong(Type type, int clientId) : type(type), clientId(clientId) {}
    PingPong(const void *data, int size);
    bool operator==(const PingPong &other);

    Type type;
    int clientId;

    void serialize(std::string *output);
    void deserialize(const void *data, int size);
    static int protoSize();
};
