// From https://www.fluentcpp.com/2020/05/22/how-to-assign-derived-classes-in-cpp/

#include <iostream>

struct AssertCompatibleTypeFailed
{
    void operator()()
    {
        assert(("Incompatible types for assignment", false));  // NOLINT
    }
};

template<typename Derived, typename Base, typename ErrorHandlingFunction = AssertCompatibleTypeFailed>
struct VirtualAssignable : Base
{
    VirtualAssignable& operator=(Base const& other) override
    {
        auto& thisDerived = static_cast<Derived&>(*this);
        if (auto* otherDerived = dynamic_cast<Derived const*>(&other))
        {
            thisDerived = *otherDerived;
        }
        else
        {
            ErrorHandlingFunction{}();
        }
        return thisDerived;  // NOLINT
    }
};


struct X
{
    virtual X& operator=(X const& other) = 0;  // NOLINT
    virtual ~X() = 0;
};

X& X::operator=(X const& other) = default;     // NOLINT
X::~X() = default;


struct A : VirtualAssignable<A, X>
{
    int value;
    explicit A(int value) : value(value){}
};

struct B : VirtualAssignable<B, X>
{
    int value;
    explicit B(int value) : value(value){}
};

int main()
{
    A a1{42};
    A a2{43};
    B b1{11};

    X& ba1 = a1;
    X& ba2 = a2;
    X& bb1 = b1;

    ba2 = ba1;
//    bb1 = ba1;   // asserts

    std::cout << "a2.value = " << a2.value << '\n';
    std::cout << "a1.value = " << a1.value << '\n';
    std::cout << "b1.value = " << b1.value << '\n';
}
