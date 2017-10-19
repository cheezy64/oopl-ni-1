// -----------
// Vector1.c++
// -----------

// http://en.cppreference.com/w/cpp/container/vector

#include <algorithm>        // copy, equal, fill
#include <cassert>          // assert
#include <cstddef>          // ptrdiff_t, size_t
#include <initializer_list> // initializer_list
#include <iostream>         // cout, endl
#include <vector>           // vector

using namespace std;

void test () {
    {
    vector<int> x;
    assert(x.size() == 0);
    }

    {
    vector<int> x(3);
    assert(x.size() == 3);
    assert(equal(begin(x), end(x), begin({0, 0, 0})));
    assert(x[1] == 0);
    x[1] = 2;
    assert(equal(begin(x), end(x), begin({0, 2, 0})));
    }

    {
    const vector<int> x(3, 2);
    assert(x.size() == 3);
    assert(equal(begin(x), end(x), begin({2, 2, 2})));
    assert(x[1] == 2);
    // x[1] = 3;                                       // error: cannot assign to return value because function 'operator[]' returns a const value
    }

    {
    const vector<int> x = {2, 3, 4};
    assert(x.size() == 3);
    assert(equal(begin(x), end(x), begin({2, 3, 4})));
    }}

int main () {
    cout << "Vector1.c++" << endl;
    test();
    cout << "Done." << endl;
    return 0;}
