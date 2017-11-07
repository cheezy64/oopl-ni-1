// ---------------------
// MethodOverriding2.c++
// ---------------------

#include <cassert>  // assert
#include <iostream> // cout, endl
#include <string>   // string, ==

struct A {
    virtual ~A() {}

    virtual std::string f (int) {
        return "A::f";}

    virtual std::string g (int) {              // note: hidden overloaded virtual function 'A::g' declared
        return "A::g";}

    virtual std::string h (int) {              // note: hidden overloaded virtual function 'A::h' declared
        return "A::h";}};

struct B : A {
    std::string f (int)  {
        return "B::f";}

    std::string g (double) {                   // warning: 'B::g' hides overloaded virtual function
        return "B::g";}

    std::string h (int) const /* override */ { // error: non-virtual member function marked 'override' hides virtual member function
        return "B::h";}};

int main () {
    using namespace std;
    cout << "MethodOverriding2.c++" << endl;

    A* const p = new B();

    assert(p->f(2) == "B::f");
    assert(p->g(2) == "A::g");
    assert(p->h(2) == "A::h");

    delete p;

    cout << "Done." << endl;
    return 0;}
