#pragma once

#include "pimpl_101_h.h"

class widget {
    class impl;
    pimpl<impl> m;

public:
    ~widget();
    void sayHello();
};
