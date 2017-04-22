#pragma once

#include "BaseMessage.h"

class BaseMessageFactory {
public:    
    virtual BaseMessage *createMessage(int type) = 0;
};