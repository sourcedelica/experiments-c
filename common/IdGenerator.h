#pragma once

#include <cstdint>

class IdGenerator {
public:
    virtual int nextId() = 0;
};

class SimpleIdGenerator : public IdGenerator {
public:
    SimpleIdGenerator(uint16_t prefix) : prefix(prefix), next(0) {};

    int nextId() {
        return static_cast<int>(prefix) << 16 | ++next;
    }

private:
    uint16_t prefix = 0;
    int16_t next = 0;
};
