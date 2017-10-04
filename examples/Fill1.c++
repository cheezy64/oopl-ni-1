// ---------
// Fill1.c++
// ---------

// http://en.cppreference.com/w/cpp/algorithm/fill

#include <algorithm> // equal, fill
#include <cassert>   // assert
#include <iostream>  // cout, endl
#include <list>      // list

using namespace std;

template <typename FI, typename T>
void my_fill (FI b, FI e, const T& v) {
    while (b != e) {
        *b = v;
        ++b;}}

void test () {
    {
    list<int>           x(5);
    list<int>::iterator b = begin(x);
    list<int>::iterator e = end(x);
    ++b;
    --e;
    fill(b, e, 2);
    assert(equal(begin(x), end(x), begin({0, 2, 2, 2, 0})));
    }

    {
    list<int>           x(5);
    list<int>::iterator b = begin(x);
    list<int>::iterator e = end(x);
    ++b;
    --e;
    my_fill(b, e, 2);
    assert(equal(begin(x), end(x), begin({0, 2, 2, 2, 0})));
    }}

int main () {
    cout << "Fill1.c++" << endl;
    test();
    cout << "Done." << endl;
    return 0;}
