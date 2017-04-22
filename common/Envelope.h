#pragma once

#include <string>
#include <caf/message_builder.hpp>

struct Envelope {
    long correlationId;
    int clientId;
    int type;
    long timeoutMs;
    bool oneWay;

    Envelope() : type(-1) {}
    Envelope(long correlationId, int clientId, int type, long timeoutMs = 0, bool oneWay = false);
    Envelope(const void *data, int size);
    Envelope(const Envelope &other);
    bool operator==(const Envelope &other);

    bool isValid() { return type != -1; }

    std::string toString() {
        std::stringstream ss;
        ss << "Envelope(correlationId=" << correlationId << ", clientId=" << clientId << ", type="
           << type << ", timeoutMs=" << timeoutMs << ", oneWay=" << oneWay;
        return ss.str();
    }

    void serialize(std::string *output) const;
    void deserialize(const void *data, int size);
    static int protoSize();

    template <class Inspector>
    friend typename Inspector::result_type inspect(Inspector &f, Envelope &e) {
        return f(
            caf::meta::type_name("Envelope"),
            e.correlationId, e.clientId, e.type, e.timeoutMs, e.oneWay
        );
    }
};
