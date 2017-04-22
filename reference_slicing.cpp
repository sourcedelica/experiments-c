#include <string>
#include <iostream>

struct Base {
    int i;

    Base(int i) : i(i) { std::cout << "Base ctor " << i << std::endl; }
    Base() : Base(42) { std::cout << "Base " << std::endl; }
    virtual ~Base() = default;
    virtual std::string toString() const { return std::to_string(i); }
};

struct Derived : public Base {
    Derived(int i, const std::string s) : Base(i), s(s) {}
    std::string s;

    virtual ~Derived() = default;
    virtual std::string toString() const { return Base::toString() + " " + s; }
};

void print(const Base &base) {
    std::cout << base.toString() << std::endl;
}

int main() {
    Derived d(2, "hey");
    print(d);
    Base base;
}
