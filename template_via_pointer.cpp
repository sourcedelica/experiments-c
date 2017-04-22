#include <string>
#include <iostream>
#include <chrono>

struct Foo {
    template<typename R, typename T>
    R sendSync(const T &request, const std::chrono::milliseconds &timeout) {
        R response;
        std::cout << request << std::endl;
        return response;
    }

    int i = 0;
};

struct Bar {
    template<typename T, typename R> R sendSync(const T &request, int timeoutMilliseconds);
};

template<typename T, typename R>
R Bar::sendSync(const T &request, int timeoutMilliseconds) {
    Foo *foo = new Foo{};
    R response = foo->sendSync<R>(request, std::chrono::milliseconds(timeoutMilliseconds));
    return response;
}

int main() {
    Bar *bar = new Bar{};

    bar->sendSync<std::string, int>(std::string{"123"}, 2000);
}