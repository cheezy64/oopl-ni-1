// ------------
// Reverse1.c++
// ------------

// http://en.cppreference.com/w/cpp/algorithm/reverse

#include <algorithm> // equal, reverse
#include <cassert>   // assert
#include <iostream>  // cout, endl
#include <list>      // list
#include <vector>    // vector

using namespace std;

template <typename BI>
void my_reverse_bi (BI b, BI e) {
    while ((b != e) && (b != --e)) {
        std::swap(*b, *e);
        ++b;}}

template <typename RI>
void my_reverse_ri (RI b, RI e) {
    while (b < --e) {
        std::swap(*b, *e);
        ++b;}}

void test () {
    {
    list<int> x = {2, 3, 4};
    reverse(begin(x), end(x));
    assert(equal(begin(x), end(x), begin({4, 3, 2})));
    }

    {
    list<int> x = {2, 3, 4, 5};
    reverse(begin(x), end(x));
    assert(equal(begin(x), end(x), begin({5, 4, 3, 2})));
    }

    {
    list<int> x = {2, 3, 4};
    my_reverse_bi(begin(x), end(x));
    assert(equal(begin(x), end(x), begin({4, 3, 2})));
    }

    {
    list<int> x = {2, 3, 4, 5};
    my_reverse_bi(begin(x), end(x));
    assert(equal(begin(x), end(x), begin({5, 4, 3, 2})));
    }

    {
    vector<int> x = {2, 3, 4};
    reverse(begin(x), end(x));
    assert(equal(begin(x), end(x), begin({4, 3, 2})));
    }

    {
    vector<int> x = {2, 3, 4, 5};
    reverse(begin(x), end(x));
    assert(equal(begin(x), end(x), begin({5, 4, 3, 2})));
    }

    {
    vector<int> x = {2, 3, 4};
    my_reverse_ri(begin(x), end(x));
    assert(equal(begin(x), end(x), begin({4, 3, 2})));
    }

    {
    vector<int> x = {2, 3, 4, 5};
    my_reverse_ri(begin(x), end(x));
    assert(equal(begin(x), end(x), begin({5, 4, 3, 2})));
    }}

int main () {
    cout << "Reverse1.c++" << endl;
    test();
    cout << "Done." << endl;
    return 0;}
