#include <iostream>

using namespace std;

struct Base {
    virtual void foo() { cout << "Base" << std::endl; }
    virtual ~Base() = default;
};

struct Child : public Base {
    ~Child() {}
};

struct Grandchild : public Child {
    virtual void foo() override { cout << "Grandchild" << std::endl; }
    ~Grandchild() {}
};


//int main() {
//    Base *b = new Grandchild;
//
//    b->foo();
//}

