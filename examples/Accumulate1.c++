// ---------------
// Accumulate1.c++
// ---------------

// http://www.cplusplus.com/reference/algorithm/accumulate/

#include <cassert>    // assert
#include <functional> // function
#include <iostream>   // cout, endl
#include <numeric>    // accumulate
#include <list>       // list

using namespace std;

template <typename II, typename T, typename BF>
T my_accumulate (II b, II e, T v, BF f) {
    while (b != e) {
        v = f(v, *b);
        ++b;}
    return v;}

void test () {
    {
    const list<int>          x = {2, 3, 4};
    function<int (int, int)> f = [] (int x, int y) -> int {return x + y;};

    assert(   accumulate(begin(x), end(x), 0, f) == 9);
    assert(my_accumulate(begin(x), end(x), 0, f) == 9);
    }

    {
    const list<int>          x = {2, 3, 4};
    function<int (int, int)> f = [] (int x, int y) -> int {return x * y;};

    assert(   accumulate(begin(x), end(x), 1, f) == 24);
    assert(my_accumulate(begin(x), end(x), 1, f) == 24);
    }}

int main () {
    cout << "Accumulate1.c++" << endl;
    test();
    cout << "Done." << endl;
    return 0;}
