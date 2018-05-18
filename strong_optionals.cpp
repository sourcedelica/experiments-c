#include <boost/optional.hpp>
#include <string>
#include <vector>
#include "NamedType.h"

template<typename T, typename NoValue>
class NamedOptional {
public:
    NamedOptional(T t) { o_ = t; };
    NamedOptional(NoValue nv) { o_ = boost::none; }
private:
    boost::optional<T> o_;
};

using FirstName = NamedType<std::string, struct FirstNameTag>;
struct AnyFirstName{};
using OptionalFirstName = NamedOptional<FirstName, AnyFirstName>;

using LastName = NamedType<std::string, struct LastNameTag>;
struct AnyLastName{};
using OptionalLastName = NamedOptional<LastName, AnyLastName>;

struct Employee {};

std::vector<Employee> findEmployees(OptionalFirstName const& firstName, OptionalLastName const& lastName) {
    return {};
}

int main(int argc, char** argv) {
    findEmployees(AnyFirstName(), LastName("Doe"));
}
