#include <iostream>
#include "pimpl_100_widget.h"

class widget::impl {
public:
    impl() = default;

    void sayHello() {
        std::cout << "Hello, world!\n";
    }
};

widget::widget() : pimpl{ new impl } { }
widget::~widget() = default;

void widget::sayHello() { pimpl->sayHello(); }