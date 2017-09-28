// ----------
// Equal1.c++
// ----------

// http://en.cppreference.com/w/cpp/algorithm/equal

#include <algorithm> // equal
#include <cassert>   // assert
#include <iostream>  // cout, endl

using namespace std;

bool my_equal (int* b, int* e, int* c) {
    while (b < e) {
        if (*b != *c)
            return false;
        ++b;
        ++c;}
    return true;}

void test () {
    int a[] = {2, 3, 4};
    int b[] = {0, 2, 3, 4, 0};

    assert(!   equal(a, a + 3, b));
    assert(!my_equal(a, a + 3, b));

    assert(   equal(a, a + 3, b + 1));
    assert(my_equal(a, a + 3, b + 1));}

int main () {
    cout << "Equal1.c++" << endl;
    test();
    cout << "Done." << endl;
    return 0;}
