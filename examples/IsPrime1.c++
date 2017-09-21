// ------------
// IsPrime1.c++
// ------------

// https://en.wikipedia.org/wiki/Primality_test

#include <cassert>  // assert
#include <cmath>    // sqrt
#include <iostream> // cout, endl

using namespace std;

bool is_prime (int n) {
    assert(n > 0);
    if ((n == 1) || ((n % 2) == 0))
        return false;
    for (int i = 3; i < std::sqrt(n); ++i)
        if ((n % i) == 0)
            return false;
    return true;}

int main () {
    cout << "IsPrime.c++" << endl;

    assert(!is_prime( 1));
    assert(!is_prime( 2));
    assert( is_prime( 3));
    assert(!is_prime( 4));
    assert( is_prime( 5));
    assert( is_prime( 7));
    assert( is_prime( 9));
    assert(!is_prime(27));
    assert( is_prime(29));

    cout << "Done." << endl;
    return 0;}
