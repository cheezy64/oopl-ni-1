// --------------
// Transform1.c++
// --------------

// http://www.cplusplus.com/reference/algorithm/transform/

#include <algorithm>  // transform, equal
#include <cassert>    // assert
#include <cmath>      // pow
#include <functional> // function
#include <iostream>   // cout, endl
#include <list>       // list
#include <vector>     // vector

using namespace std;

template <typename II, typename OI, typename UF>
OI my_transform (II b, II e, OI x, UF f) {
    while (b != e) {
        *x = f(*b);
        ++b;
        ++x;}
    return x;}

void test () {
    {
    const list<int>       x = {2, 3, 4};
    vector<int>           y(5);
    function<int (int)>   f = [] (int n) -> int {return pow(n, 2);};
    vector<int>::iterator q = transform(begin(x), end(x), begin(y) + 1, f);
    assert(q == begin(y) + 4);
    assert(equal(begin(y), end(y), begin({0, 4, 9, 16, 0})));
    }

    {
    const int p = 2;
    const list<int>       x = {2, 3, 4};
    vector<int>           y(5);
    function<int (int)>   f = [p] (int n) -> int {return pow(n, p);};
    vector<int>::iterator q = my_transform(begin(x), end(x), begin(y) + 1, f);
    assert(q == begin(y) + 4);
    assert(equal(begin(y), end(y), begin({0, 4, 9, 16, 0})));
    }}

int main () {
    cout << "Transform1.c++" << endl;
    test();
    cout << "Done." << endl;
    return 0;}
