#include <iostream>
#include <cstdarg>
#include <experimental/optional>
#include <experimental/string_view>
#include <unordered_map>
#include <vector>

using namespace std;
using namespace std::literals;
using std::experimental::optional;
using std::experimental::string_view;

// #Val is stringify
#define ENUM_NAME(Val)  #Val

enum class EnumClass {
    One, Two
};

enum Enum {
    EOne, ETwo
};

struct Test {
    int i = 42;

    Test() { cout << "ctor" << endl; }

    // Add -Wdeprecated to make clang complain about generated copy ctor since ~Test() exists
//    Test(const Test& other) = delete;
//    Test(const Test& other) : i(other.i) { cout << "copy ctor" << endl; }

    // error: mem-initializer for 'Test::i' follows constructor delegation
//    Test(int i) : Test(), i(i) {}

    Test(int i) : i(i) {}

    Test& operator=(const Test& other) {
        i = other.i;
        cout << "copy assign" << endl;
        return *this;
    }

    ~Test() { cout << "dtor" << endl; }
};

class Test2 {
public:
    int i;
    char c;

    Test2() {}

    Test2(int i, char c) : i(i), c(c) {}

    Test2& operator=(Test2 copy) {
        swap(*this, copy);
        return *this;
    }

    Test2(Test2&& other) : Test2() {
        swap(*this, other);
    }

    Test2(const Test2& other) = default;

    friend void swap(Test2& a, Test2& b) {
        using std::swap;
        swap(a.i, b.i);
        swap(a.c, b.c);
    }
};

class Holder {
public:
    static void create() {
        cout << "make shared test" << endl;
        test_ = make_shared<Test>();
        atexit([](){ Holder::drop(); });
    }

    static void drop() {
        cout << "reset shared test" << endl;
        test_.reset();
    }

    static int deref() {
        return test_ != nullptr ? test_->i : -1;
    }

    static shared_ptr<Test> &giveRef() { return test_; }

private:
    static shared_ptr<Test> test_;
};

shared_ptr<Test> Holder::test_;

void print(const char *, ...);
void printString(const int i, const char **strings);

template <typename T>
void func(T &param) {
    param = 0;
}

template <typename T>
unique_ptr<T> giveBack(unique_ptr<T> ptr) {
    return ptr;
}

void someFun() {
    std::cout << "We're certainly having some fun" << std::endl;
}

template <typename Fun>
struct FunSaver {
    Fun &fun;

    FunSaver(Fun &fun_in) : fun(fun_in) {}

    void call() { fun(); }
};

template <typename Fun>
void callAFun(Fun &fun) {
    fun();
}

optional<int> testOptional() {
    optional<int> oi1 = 1;
    optional<int> oi2 = optional<int>(2);
    optional<int> oi3(3);
    return optional<int>{};
}

Test returnTest1() {
    Test t;
    return t;
}

Test returnTest2() {
    return Test{};
}

void printStringView(string_view sv) {
    std::cout << "String view: " << sv << std::endl;
}

int main() {
    cout << ENUM_NAME(EnumClass::One) << ' ' << ENUM_NAME(EnumClass::Two) << std::endl;
    cout << ENUM_NAME(EOne) << ' ' << ENUM_NAME(Enum::ETwo)<< std::endl;

    char buffer[128];
    int precision = 12;
    double value = 123.456;
    snprintf(buffer, sizeof(buffer), "%.*f", precision, value);
    cout << buffer << endl;

    Test t(5);
    cout << "t.i is " << t.i << endl;

    std::string orbits("365.24 29.53");

    const char* strings[3] = {"hey", "there", "dude"};
    printString(1, strings);

    Holder::deref();
    Holder::create();
    auto ts = make_shared<Test>(7);
    auto &href = Holder::giveRef();
    href = ts;
    cout << "Holder has " << Holder::deref() << '\n';

    print("str: %s %d %.2f\n", "hey there", 2, 3.14);

    int i = 5;
    func(i);
    std::cout << "i is now " << i << std::endl;

    Test2 t2{42, 'z'};
    Test2 t2b;
    t2b = t2;
    auto f = [](){ return Test2{101, 'a'}; };
    Test2 t2c{f()};
    std::cout << "t2b=" << t2b.i << " " << t2b.c << std::endl;
    std::cout << "t2c=" << t2c.i << " " << t2c.c << std::endl;

    unique_ptr<string> sptr = make_unique<string>("abc");
    unique_ptr<string> sptr2 = giveBack(std::move(sptr));  // function result is a temporary thus unique_ptr&&
    cout << *sptr2 << endl;

    if (!testOptional()) cout << "Empty optional" << endl;

    cout << returnTest1().i << endl;
    cout << returnTest2().i << endl;

//    TestUint16 tu16a;

    FunSaver<decltype(someFun)> fs(someFun);
    fs.call();
//    callAFun(someFun);

//    cout << "this is a sv string literal"sv << std::endl;
    printStringView("a string literal");

    return 0;
}


void print(const char *format, ...) {
    va_list args;
    va_start(args, format);

    vprintf(format, args);
}

void printString(const int i, const char **strings) {
    cout << strings[i] << endl;
}