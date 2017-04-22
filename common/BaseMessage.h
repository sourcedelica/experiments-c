#pragma once

#include <string>
#include "caf/message_builder.hpp"

struct BaseMessage {
    int id;
    int type;
    int version;

    BaseMessage() {}
    BaseMessage(const BaseMessage &msg) { id = msg.id; type = msg.type; version = msg.version; }
    BaseMessage(int typeId, int version) : type(typeId), version(version) {}
    BaseMessage& operator=(const BaseMessage &msg) = default;
    virtual ~BaseMessage() {}

    virtual std::string toString() const { return "BaseMessage type " + std::to_string(type); }

    virtual void serialize(std::string *output) const = 0;
    virtual void deserialize(const void *data, int size) = 0;

    virtual void appendMessage(caf::message_builder &messageBuilder) const = 0;

    template <class Inspector>
    friend typename Inspector::result_type inspect(Inspector &f, BaseMessage &bm) {
        return f(bm.type, bm.version);
    }
};

/**
 * Takes ownership of a BaseMessage* and deletes it when it goes out of scope
 * For use with pre-C++11 compilers.  For apps that only run on C++11 or greater,
 * use unique_ptr<BaseMessage>.
 */
class ScopedBaseMessagePtr {
public:
    ScopedBaseMessagePtr(BaseMessage *message) : pMessage(message) {}
    ~ScopedBaseMessagePtr() {
        if (pMessage) delete pMessage;
    }
    operator BaseMessage*() const { return pMessage; }

    operator bool() const { return pMessage != 0; }

    BaseMessage &operator*() const { return *pMessage; }
    BaseMessage *operator->() const { return pMessage; }
    BaseMessage *get() const { return pMessage; }

private:
    BaseMessage *pMessage;
};
