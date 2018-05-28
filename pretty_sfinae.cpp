#include <type_traits>
#include <iostream>

// From https://www.fluentcpp.com/2018/05/15/make-sfinae-pretty-1-what-value-sfinae-brings-to-code/
template<typename T>
class MyClass1
{
public:
    void f(T const& x) {
        std::cout << "T const &: " << x << std::endl;
    }

    // Fails to compile if T is a reference type
//    void f(T&& x) {
//        std::cout << "T&&: " << x << std::endl;
//    }

    template<typename T_ = T>
    void f(T&& x,
           typename std::enable_if<!std::is_reference<T_>::value,
                                   std::nullptr_t>::type = nullptr) {
        std::cout << "T&&: " << x << std::endl;
    }
};

// The prettier version
// from https://www.fluentcpp.com/2018/05/18/make-sfinae-pretty-2-hidden-beauty-sfinae/
template<typename T>
using IsNotReference = std::enable_if_t<!std::is_reference<T>::value>;

template<typename T>
class MyClass2
{
public:
    void f(T const& x) {
        std::cout << "T const &: " << x << std::endl;
    }

    template<typename T_ = T, typename = IsNotReference <T_>>
    void f(T&& x) {
        std::cout << "T&&: " << x << std::endl;
    }
};

int main(int argc, const char **argv) {
    MyClass1<int> myClass1a;
    myClass1a.f(argc);

    MyClass1<int &> myClass1b;
    myClass1b.f(argc);

    MyClass2<int> myClass2a;
    myClass2a.f(argc);

    MyClass2<int &> myClass2b;
    myClass2b.f(argc);
}