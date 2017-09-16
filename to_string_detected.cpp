#include <iostream>

// Adapted from http://www.fluentcpp.com/2017/06/06/using-tostring-custom-types-cpp/
// Another good explanation is at https://blog.tartanllama.xyz/detection-idiom/
// Reference implementation for C++17: http://en.cppreference.com/w/cpp/experimental/is_detected
#include "to_string_detected.h"

// Has member to_string()
struct HasToString {
    std::string to_string() const {
        return "HasToString";
    }
};

// Has non-member to_string(const T&)
struct HasNonMemberToString {};
std::string to_string(const HasNonMemberToString &hts) {
    return "HasNonMemberToString";
}

// Has operator<<(&os, const T&)
struct HasOStream {};
std::ostream &operator<<(std::ostream &os, const HasOStream &hos) {
    os << "HasOStream";
    return os;
}

int main(int argc, char **argv) {
    std::string htsStr = toString(HasToString{});
    std::cout << htsStr << '\n';

    std::string hnmtsStr = toString(HasNonMemberToString{});
    std::cout << hnmtsStr << '\n';

    std::string hosStr = toString(HasOStream{});
    std::cout << hosStr << '\n';

    std::string intStr = toString(42);
    std::cout << intStr << '\n';
}
