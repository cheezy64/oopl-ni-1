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
    cout << "1. ctor: ";
    B<int> x;             // 1. ctor: A() B()
    cout << endl;

    {
    cout << "2. copy: ";
    B<int> y = f();       // 2. copy: A() B() ~B() ~A()
    }
    cout << endl;

    cout << "3. copy: ";
    x = f();              // 3. copy: A() B() =(const A&) =(const B&) ~B() ~A()
    cout << endl;

    cout << "4. dtor: ";
    }                     // 4. dtor: ~B() ~A()
    cout << endl << endl;



    {
    cout << "1. ctor: ";
    C<int> x;            // 1. ctor: A() C()
    cout << endl;

    {
    cout << "2. copy: ";
    C<int> y = g();      // 2. ctor: A() C() ~C() ~A()
    }
    cout << endl;

    cout << "3. move: ";
    x = g();             // 3. copy: A() C() =(A&&) =(C&&) ~C() ~A()
    cout << endl;

    cout << "4. dtor: ";
    }                    // 4. dtor: ~C() ~A()
    cout << endl;

    return 0;}

/*
1. ctor: A() B()
2. copy: A() B() ~B() ~A()
3. copy: A() B() =(const A&) =(const B&) ~B() ~A()
4. dtor: ~B() ~A()

1. ctor: A() C()
2. copy: A() C() ~C() ~A()
3. move: A() C() =(A&&) =(C&&) ~C() ~A()
4. dtor: ~C() ~A()
*/
