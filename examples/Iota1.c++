// ---------
// Iota1.c++
// ---------

// http://en.cppreference.com/w/cpp/algorithm/iota

#include <algorithm> // equal
#include <cassert>   // assert
#include <iostream>  // cout, endl
#include <list>      // list
#include <numeric>   // iota

using namespace std;

template <typename FI, typename T>
void my_iota (FI b, FI e, T v) {
    while (b != e) {
        *b = v;
        ++b;
        ++v;}}

void test () {
    {
    list<int>           x(5);
    list<int>::iterator b = begin(x);
    list<int>::iterator e = end(x);
    ++b;
    --e;
    iota(b, e, 2);
    assert(equal(begin(x), end(x), begin({0, 2, 3, 4, 0})));
    }

    {
    list<int>           x(5);
    list<int>::iterator b = begin(x);
    list<int>::iterator e = end(x);
    ++b;
    --e;
    my_iota(b, e, 2);
    assert(equal(begin(x), end(x), begin({0, 2, 3, 4, 0})));
    }}

int main () {
    cout << "Iota1.c++" << endl;
    test();
    cout << "Done." << endl;
    return 0;}
