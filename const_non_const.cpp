#include <iostream>

struct S {
private:
    int i = 0;

    template<typename Self>
    static decltype(auto) get_i_common(Self *self) {
        return &self->i;
    }

public:
    int* get_i() {
        std::cout << "Called non-const get_i()\n";
        return get_i_common(this);
    }

    const int* get_i() const {
        std::cout << "Called const get_i()\n";
        return get_i_common(this);
    }
};

int main() {
    S s;
    const S cs;

    s.get_i();
    cs.get_i();
}
