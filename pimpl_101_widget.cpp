#include <iostream>
#include "pimpl_101_widget.h"
#include "pimpl_101_impl.h"

class widget::impl {
public:
    void sayHello() {
        std::cout << "Hello, world!\n";
    }
};

widget::~widget() = default;

void widget::sayHello() { m->sayHello(); }

template class pimpl<widget::impl>;
