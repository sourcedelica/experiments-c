#pragma once

#include <memory>

class widget {
public:
    widget();
    ~widget();

    void sayHello();

private:
    class impl;
    std::unique_ptr<impl> pimpl;
};
