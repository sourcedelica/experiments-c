#pragma once

#include <string>
#include <sstream>
#include <cstring>

// TODO - switch CAF version to use this instead of atoms?
struct Registration {
    constexpr static size_t MaxEndpointLength = 256;

    enum Type { Register, Unregister, Registered, Unregistered };

    std::string TypeName(Type type) const {
        switch (type) {
            case Register:     return "register";
            case Unregister:   return "unregister";
            case Registered:   return "registered";
            case Unregistered: return "unregistered";
        }
        return "Invalid registration type";
    }

    Type type;
    int clientId;
    char endpoint[MaxEndpointLength];

    Registration() {};
    Registration(Type type) : type(type) {}
    Registration(Type type, int clientId, const std::string &endpoint)
            : type(type), clientId(clientId) {
        strncpy(this->endpoint, endpoint.c_str(), MaxEndpointLength);
    }
    Registration(const void *data, int size);

    std::string toString() const {
        std::stringstream ss;
        ss << "Registration(" << TypeName(type) << "," << clientId << ")";
        return ss.str();
    }

    bool operator==(const Registration &other);

    void serialize(std::string *output);
    void deserialize(const void *data, int size);
    static int protoSize();
};