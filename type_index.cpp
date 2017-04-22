#include <boost/type_index.hpp>
#include <iostream>

using std::cout;
using boost::typeindex::type_id_with_cvr;

template<typename T>
void fr(const T& param) {
    // show T
    cout << "T =     "
         << type_id_with_cvr<T>().pretty_name()
         << '\n';

    // show param's type
    cout << "param = "
         << type_id_with_cvr<decltype(param)>().pretty_name()
         << '\n';
}

template<typename T>
void fv(const T param) {
    // show T
    cout << "T =     "
         << type_id_with_cvr<T>().pretty_name()
         << '\n';

    // show param's type
    cout << "param = "
         << type_id_with_cvr<decltype(param)>().pretty_name()
         << '\n';
}

template<typename T>
void fp(const T* param) {
    // show T
    cout << "T =     "
         << type_id_with_cvr<T>().pretty_name()
         << '\n';

    // show param's type
    cout << "param = "
         << type_id_with_cvr<decltype(param)>().pretty_name()
         << '\n';
}

template<typename T>
void ffr(T&& param) {
    // show T
    cout << "T =     "
         << type_id_with_cvr<T>().pretty_name()
         << '\n';

    // show param's type
    cout << "param = "
         << type_id_with_cvr<decltype(param)>().pretty_name()
         << '\n';
}


int foo(int i) {
    return 0;
}

template <typename T>
struct ST {
    T t;
};

int main() {
    int i = 0;
    auto &ri = i;
    const auto &cri = i;
    auto *pi = &i;
    ST<int> st{i};

    cout << "fr(const T& param)\n";
    fr(1);
    fr(i);
    fr(ri);
    fr(cri);
    fr(pi);
    fr(foo);
    fr(st);

    cout << "\n" << "fv(const T param)\n";
    fv(1);
    fv(i);
    fv(ri);
    fv(cri);
    fv(pi);
    fv(foo);
    fv(st);

    cout << "\n" << "fp(const T* param)\n";
    fp(pi);
    fp(foo);

    cout << "\n" << "ffr(T&& param)\n";
    ffr(1);
    ffr(i);
    ffr(ri);
    ffr(cri);
    ffr(pi);
    ffr(foo);
    ffr(st);
}