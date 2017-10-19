// -----------------------
// FunctionOverloading.c++
// -----------------------

// http://www.cplusplus.com/doc/tutorial/functions2/

// ad-hoc compile-time polymorphism

#include <cassert>  // assert
#include <cstring>  // strcmp
#include <iostream> // cout, endl
#include <string>   // string

using namespace std;

string f (int) {              // l-value or r-value
    return "f(int)";}

//string f (const int) {      // error: redefinition of "string f(int)"
//    return "f(const int)";}



string g (int&) {             // non-const l-value
    return "g(int&)";}



string h (const int&) {       // l-value or r-value
    return "h(const int&)";}



string m (int&&) {            // r-value
    return "m(int&&)";}



string p (int&) {             // non-const l-value
    return "p(int&)";}

string p (const int&) {       // const l-value or r-value
    return "p(const int&)";}



string q (int&) {             // non-const l-value
    return "q(int&)";}

string q (int&&) {            // r-value
    return "q(int&&)";}



string r (const int&) {       // l-value
    return "r(const int&)";}

string r (int&&) {            // r-value
    return "r(int&&)";}



string s (int&) {             // non-const l-value
    return "s(int&)";}

string s (const int&) {       // const l-value
    return "s(const int&)";}

string s (int&&) {            // r-value
    return "s(int&&)";}



int main () {
    cout << "FunctionOverloading.c++" << endl;

    {
          int i  = 2;
    const int ci = 3;

    assert(f(i)  == "f(int)");
    assert(f(ci) == "f(int)");
    assert(f(4)  == "f(int)");

    assert(g(i)  == "g(int&)");
//  g(ci);                            // error: no matching function for call to 'g'
//  g(4);                             // error: no matching function for call to 'g'

    assert(h(i)  == "h(const int&)");
    assert(h(ci) == "h(const int&)");
    assert(h(4)  == "h(const int&)");

//  assert(m(i)  == "m(int&&)");      // error: no matching function for call to 'm'
//  assert(m(ci) == "m(int&&)");      // error: no matching function for call to 'm'
    assert(m(4)  == "m(int&&)");

    assert(p(i)  == "p(int&)");
    assert(p(ci) == "p(const int&)");
    assert(p(4)  == "p(const int&)");

    assert(q(i)  == "q(int&)");
//  q(ci);                            // error: no matching function for call to 'q'
    assert(q(4)  == "q(int&&)");

    assert(r(i)  == "r(const int&)");
    assert(r(ci) == "r(const int&)");
    assert(r(4)  == "r(int&&)");

    assert(s(i)  == "s(int&)");
    assert(s(ci) == "s(const int&)");
    assert(s(4)  == "s(int&&)");
    }

    cout << "Done." << endl;
    return 0;}
