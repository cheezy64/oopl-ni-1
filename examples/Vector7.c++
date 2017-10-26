// -----------
// Vector7.c++
// -----------

// http://en.cppreference.com/w/cpp/container/vector

#include <algorithm>        // equal
#include <cassert>          // assert
#include <initializer_list> // initializer_list
#include <iostream>         // cout, endl
#include <memory>           // allocator
#include <utility>          // !=, <=, >, >=, move
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
    }

    {
    const vector<int> x(10, 2);
    const vector<int> y = x;
    assert(begin(x) != begin(y));
    assert(x == y);
    }

    {
    const vector<int> x(20, 3);
          vector<int> y(10, 2);
    y = x;
    assert(begin(x) != begin(y));
    assert(x == y);
    }

    {
    const vector<int> x(10, 2);
    const vector<int> y(10, 2);
    const vector<int> z(10, 3);
    assert(x == y);
    assert(x <= y);
    assert(x >= y);
    assert(x != z);
    assert(x <  z);
    assert(z >  x);
    }

    {
    vector<int>           x(10, 2);
    vector<int>::iterator b = begin(x);
    const vector<int>     y = move(x);
    assert(x.size() ==  0);
    assert(y.size() == 10);
    assert(b        == begin(y));
    }

    {
    vector<int>           x(20, 3);
    vector<int>           y(10, 2);
    vector<int>::iterator b = begin(x);
    y = move(x);
    assert(x.size() ==  0);
    assert(y.size() == 20);
    assert(b        == begin(y));
    }

    {
    const vector<int> x(3, 2, allocator<int>());
    assert(equal(begin(x), end(x), begin({2, 2, 2})));
    }}

int main () {
    cout << "Vector7.c++" << endl;
    test();
    cout << "Done." << endl;
    return 0;}
