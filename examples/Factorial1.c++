// --------------
// Factorial1.c++
// --------------

#include <cassert>    // assert
#include <functional> // function
#include <iostream>   // cout, endl
#include <numeric>    // accumulate, iota
#include <vector>     // vector

using namespace std;

// recursive procedure
// linear recursive process
int factorial_recursion (int n) {
    assert(n >= 0);
    if (n < 2)
        return 1;
    return n * factorial_recursion(n - 1);}

int factorial_tail_recursion_aux (int n, int m) {
    assert(n >= 0);
    assert(m >= 1);
    if (n < 2)
        return m;
    return factorial_tail_recursion_aux(n - 1, n * m);}

// recursive procedure
// linear iterative process
int factorial_tail_recursion (int n) {
    assert(n >= 0);
    return factorial_tail_recursion_aux(n, 1);}

// iterative procedure
// linear iterative process
int factorial_iteration (int n) {
    assert(n >= 0);
    int v = 1;
    while (n > 1) {
        v *= n;
        --n;}
    return v;}

// iterative procedure
// linear iterative process
int factorial_accumulate (int n) {
    assert(n >= 0);
    vector<int> x(n);
    iota(x.begin(), x.end(), 1);
    const int v = accumulate(x.begin(), x.end(), 1, [] (int x, int y) -> int {return x * y;});
    return v;}

void test (function<int (int)> f) {
	assert(f(0) == 1);
	assert(f(1) == 1);
	assert(f(2) == 2);
	assert(f(3) == 6);
	assert(f(4) == 24);
	assert(f(5) == 120);}

int main () {
    cout << "Factorial1.c++" << endl;
    test(factorial_recursion);
    test(factorial_tail_recursion);
    test(factorial_iteration);
    test(factorial_accumulate);
    cout << "Done." << endl;
    return 0;}
