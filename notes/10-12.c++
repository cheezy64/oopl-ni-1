// -----------
// Thu, 12 Oct
// -----------

/*
nested classes
Range
implicit type conversion
initializations
initializer_list
auto
*/

struct C {};

struct A {
    int i;

    private:
        struct B {    // nested class
            int j;}}

int main () {
    A x;
    x.i = 2;

    B y;    // not ok
    A::B y;

    C z;

    vector<int> x(10, 2);
    vector<int>::iterator p = begin(x);

    list<int> y(10, 2);
    list<int>::iterator p = begin(x);

class A {
    private:
        int i;

    public:
        class B {
            friend class A;

            private B ()
                {}

            int j;};

        B f () {
            return B();}};

int main () {
    A x;
    x.i = 2;

    B y;    // not ok
    A::B y; // not ok

    A::B p = x.f();

struct A {
    A (int) {}};

void f (A z) {}

int main () {
    A x = 2;
    A y(2);

    f(x);
    f(A(2));
    f(2);

struct B {
    explicit B (int) {}};

void f (B z) {}

int main () {
    B x = 2; // not ok
    B y(2);

    f(x);
    f(B(2));
    f(2);    // not ok

struct A {
    A (int) {}

    bool operator == (const A& rhs) const {
        return ...}};

int main () {
    const A x = 2;
    const A y = 2;
    cout << (x == y); // x.operator==(y)

    cout << (x == 2); // x.operator==(2)

    cout << (2 == x); // not ok

class A {
    friend bool operator == (const A& lhs, const A& rhs) {
        return lhs._i == rhs._i;}

    private:
        int _i;

    public:
        A (int i) :
            _i (i)
            {}};

int main () {
    const A x = 2;
    const A y = 2;
    cout << (x == y); // operator==(x, y);

    cout << (x == 2); // operator==(x, 2);

    cout << (2 == x); // operator==(2, x);

/*
== is a symmetric operator

other symmetric operator
    +, -, *, /, <, &, |, &&, ||, >, <=, >=
*/

template <typename T>
class vector {
    private:
        ...

    public:
        explicit vector (int s) {
            ...}};

void f (vector<int> y) {}

int main () {
    vector<int> x(10000);
    f(x);
    f(10000); // not ok

class string {
    private:
        ...

    public:
        string (const char*) {...}};

void f (string t) {}

int main () {
    string s("abc");
    f(s);
    f("abc");

template <typename T>
class vector {
    private:
        ...

    public:
        vector (int s, const T& v) {
            ...}

        vector (initializer_list<T> other) {
            ...}};

int main () {
    vector<double> x(10, 2.34); // size 10, values 2.34

    vector<double> y{10, 2.34}; // size 2, values 10 and 2.34

    vector<double> z = {10, 2.34};

struct A {
    A () {}
    A (int) {}
    A (int, int) {}};

int main () {
    A x(2, 3); // two int constr
    A y(2);    // one int constr
    A z();     // a function named z, that takes nothing, and returns an A
    A t;       // zero arg constr
