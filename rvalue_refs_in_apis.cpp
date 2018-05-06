#include <utility>

// From https://foonathan.net/blog/2018/03/26/rvalue-references-api-guidelines.html

struct Bar {};
struct Baz {};

class Foo
{
private:
    Bar bar_;
    Baz baz_;
};

class Builder
{
public:
    void set_bar(Bar b) { }

    void set_baz(Baz b) { }

    Foo&& finish() &&
    {
        return std::move(obj_);
    }

private:
    Foo obj_;
};

int main() {
    Builder builder;
    builder.set_bar(Bar{});

    auto obj = builder.finish(); // error!
    auto obj2 = std::move(builder).finish(); // okay
}
