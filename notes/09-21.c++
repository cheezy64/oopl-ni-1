// -----------
// Thu, 21 Sep
// -----------

/*
using
operator overloading
Collatz Conjecture
assertions
Google Test
gcov
l-values / r-values
pre  increment
post increment

exceptions
types
*/

int f () {
    return 2;}

/*
What does f() return?
    the return type  is int
    the return value is 2

In C there are no exceptions.
*/

int f (...) {
    ...
    if (<something wrong>) {
        return -1;
    ...

int g (...) {
    ...
    int i = f(...);
    if (i == -1)
        <something wrong>
    ...

...
...g(...)...
...

int h;

int f (...) {
    ...
    h = 0;
    if (<something wrong>) {
        h = -1;
        return ...}
    ...

int g (...) {
    ...
    int i = f(...);
    if (h == -1)
        <something wrong>
    ...

...
...g(...)...
...

int f (..., int& e2) {
    ...
    if (<something wrong>) {
        e2 = -1;
        return ...}
    ...

int g (...) {
    ...
    int e = 0;
    int i = f(..., e);
    if (e == -1)
        <something wrong>
    ...

...
...g(...)...
...

int f (...) {
    ...
    if (<something wrong>) {
        Child_of_E x(...);
        throw x;
    ...

int g (...) {
    ...
    try {
        ...
        int i = f(...);
        ...}
    catch (E& e)
        <something wrong>
    ...

...
...g(...)...
...

Child_of_E x(...);
E          y(...);
x = y;    // not ok
y = x;    // ok, undesirable, because it's slicing

Child_of_E* p = x;  // not ok
Child_of_E* p = &x;
p = &y;             // not ok

E* q = &y;
q = &x;
Child_of_E* r = q;                           // not ok
Child_of_E* r = static_cast<Child_of_E*>(q);

/*
In C, strings are arrays of chars with a terminating null, char*.

In C++, strings are a user-defined type, std::string

How does:
    std::string == char*
work?

1. There's an overload of == with std::string and char*.
2. There's an implicit conversion from std::string to char*.
3. There's an implicit conversion from char* to std::string.
*/

struct A {
    explicit A (int) {}};

void f (A y) {}

int main () {
    A x(2);
    f(x);
    f(A(2));
    f(2);    // not ok with explicit

/*
What's the cost of adding elements to a vector?
    at the back:   O(1), amortized
    anywhere else: O(n)

What's the cost of removing elements from a vector?
    at the back:   O(1)
    anywhere else: O(n)

What's the cost of indexing elements of a vector?
    O(1)
*/
