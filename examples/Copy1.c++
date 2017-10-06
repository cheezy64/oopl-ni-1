// ---------
// Copy1.c++
// ---------

// http://en.cppreference.com/w/cpp/algorithm/copy

#include <algorithm> // copy, equal
#include <cassert>   // assert
#include <iostream>  // cout, endl
#include <list>      // list
#include <vector>    // vector

using namespace std;

template <typename II, typename OI>
OI my_copy (II b, II e, OI x) {
    while (b != e) {
        *x = *b;
        ++b;
        ++x;}
    return x;}

void test () {
    {
    const list<int>       x = {2, 3, 4};
    vector<int>           y(5);
    vector<int>::iterator p = copy(begin(x), end(x), begin(y) + 1);
    assert(p == begin(y) + 4);
    assert(equal(begin(y), end(y), begin({0, 2, 3, 4, 0})));
    }

    {
    const list<int>       x = {2, 3, 4};
    vector<int>           y(5);
    vector<int>::iterator p = my_copy(begin(x), end(x), begin(y) + 1);
    assert(p == begin(y) + 4);
    assert(equal(begin(y), end(y), begin({0, 2, 3, 4, 0})));
    }}

int main () {
    cout << "Copy1.c++" << endl;
    test();
    cout << "Done." << endl;
    return 0;}
