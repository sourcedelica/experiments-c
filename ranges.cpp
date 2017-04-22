#include <vector>
#include <range/v3/all.hpp>
#include <iostream>

using namespace std;
using namespace ranges;

int main() {
    vector<int> vi{1, 2, 3, 4, 5};
    auto rng = vi | view::transform([](int i) { return i * 2; })
                  | view::filter([](int i) { return i != 6; });

    for (auto i : rng) {
        cout << i << endl;
    }
}

