// -------------------
// Initializations.c++
// -------------------

// http://en.cppreference.com/w/cpp/language/value_initialization
// http://en.cppreference.com/w/cpp/language/initializer_list
// http://en.cppreference.com/w/cpp/utility/initializer_list

#include <cassert>          // assert
#include <initializer_list> // initializer_list
#include <iostream>         // cout, endl
#include <vector>           // vector

using namespace std;

struct A {
    A (int)
        {}};

struct B {
    explicit B (int)
        {}};

struct C {
    C (initializer_list<int> l)
        {}};

struct D {
    D (int)
        {}

    D (initializer_list<int> l)
        {}};

int main () {
    cout << "Initializations.c++" << endl;

    {
    int i(2);
    assert(i == 2);

    int j = 2;
    assert(j == 2);

    j = 3;
    assert(j == 3);

    int k{2};       // C++11 initializer_list
    assert(k == 2);

    int m = {2};    // C++11 initializer_list
    assert(m == 2);

    m = {3};
    assert(m == 3);
    }



    {
    int i(2.0);
    assert(i == 2);

    int j = 2.0;
    assert(j == 2);

//  int k{2.0};     // error: type 'double' cannot be narrowed to 'int' in initializer list [-Wc++11-narrowing]
//  int m = {2.0};  // error: type 'double' cannot be narrowed to 'int' in initializer list [-Wc++11-narrowing]
    }



    {
    A x(2);
    assert(&x == &x);

    A y = 2;
    assert(&y == &y);

    y = 3;
    assert(&y == &y);

    A z{2};
    assert(&z == &z);

    A t = {2};
    assert(&t == &t);

    t = {3};
    assert(&t == &t);
    }



    {
    B x(2);
    assert(&x == &x);

//  B y = 2;          // error: no viable conversion from 'int' to 'B'

    B z{2};
    assert(&z == &z);

//  B t = {2};        // error: chosen constructor is explicit in copy-initialization
//  t = {3};          // error: no viable overloaded '='
    }



    {
//  C x(2);           // error: no matching constructor for initialization of 'C'
//  C y = 2;          // error: no viable conversion from 'int' to 'C'

    C z{2};
    assert(&z == &z);

    C t = {2};
    assert(&t == &t);

    t = {3};
    assert(&t == &t);
    }



    {
    D x(2);
    assert(&x == &x);

    D y = 2;
    assert(&y == &y);

    D z{2};
    assert(&z == &z);

    D t = {2};
    assert(&t == &t);

    t = {3};
    assert(&t == &t);
    }



    {
//  initializer_list<int> x(2);    // error: no matching constructor for initialization of 'initializer_list<int>'
//  initializer_list<int> y = 2;   // error: no viable conversion from 'int' to 'initializer_list<int>'

    initializer_list<int> z{2};
    assert(&z == &z);

    initializer_list<int> t = {2};
    assert(&t == &t);

    t = {3};
    assert(&t == &t);
    }



    {
    vector<int> x(2);
    assert(x.size() == 2);
    assert(equal(begin(x), end(x), begin({0, 0})));

//  vector<int> y = 2;                                 // error: no viable conversion from 'int' to 'vector<int>'

    vector<int> z{2};
    assert(z.size() == 1);
    assert(equal(begin(z), end(z), begin({2})));

    vector<int> t = {2};
    assert(t.size() == 1);
    assert(equal(begin(t), end(t), begin({2})));

    t = {3};
    assert(t.size() == 1);
    assert(equal(begin(t), end(t), begin({3})));
    }

    cout << "Done." << endl;
    return 0;}
