// --------
// Move.c++
// --------

#include <cassert>  // assert
#include <iostream> // cout, endl
#include <utility>  // move

using namespace std;

template <typename T>
struct A {
    A () {
        cout << "A() ";}

    A (const A& rhs) {             // copy constructor
        cout << "A(const A&) ";}

    A (A&&) {                      // move constructor
        cout << "A(A&&) ";}

    A& operator = (const A&) {     // copy assignment
        cout << "=(const A&) ";
        return *this;}

    A& operator = (A&&) {          // move assignment
        cout << "=(A&&) ";
        return *this;}

    ~A() {
        cout << "~A() ";}};

template <typename T>
struct B {
    A<T> _x;                       // containment

    B () :
            _x () {
        cout << "B() ";}

    B (const B& rhs) :
            _x (rhs._x) {
        cout << "B(const B&) ";}

    B& operator = (const B& rhs) {
        _x = rhs._x;
        cout << "=(const B&) ";
        return *this;}

    ~B() {
        cout << "~B() ";}};

template <typename T>
struct C {
    A<T> _x;                       // containment

    C () :
            _x () {
        cout << "C() ";}

    C (const C& rhs) :
            _x (rhs._x) {
        cout << "C(const C&) ";}

    C (C&& rhs) :
            _x (move(rhs._x)) {
        cout << "C(C&&) ";}

    C& operator = (const C& rhs) {
        _x = rhs._x;
        cout << "=(const C&) ";
        return *this;}

    C& operator = (C&& rhs) {
        _x = move(rhs._x);
        cout << "=(C&&) ";
        return *this;}

    ~C() {
        cout << "~C() ";}};

B<int> f () {
    B<int> z;
    return z;}

C<int> g () {
    C<int> z;
    return z;}

int main() {
    {
    cout << "1. copy: ";
    B<int> x = f();      // 1. copy: A() B()
    }
    cout << endl;

    {
    cout << "2. asgn: ";
    B<int> x;
    x = f();             // 2. asgn: A() B() =(const A&) =(const B&)
    }
    cout << endl << endl;

    {
    cout << "1. copy: ";
    C<int> x = g();      // 1. copy: A() C()
    }
    cout << endl;

    {
    cout << "2. asgn: ";
    C<int> x;
    x = g();             // 2. asgn: A() C() =(A&&) =(C&&)
    }
    cout << endl;

    return 0;}

/*
1. copy: A() B() ~B() ~A()
2. asgn: A() B() A() B() =(const A&) =(const B&) ~B() ~A() ~B() ~A()

1. copy: A() C() ~C() ~A()
2. asgn: A() C() A() C() =(A&&) =(C&&) ~C() ~A() ~C() ~A()
*/
