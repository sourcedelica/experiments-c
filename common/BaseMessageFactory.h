#pragma once

class BaseMessage;

class BaseMessageFactory {
public:
    virtual BaseMessage *createMessage(int type) = 0;
};
