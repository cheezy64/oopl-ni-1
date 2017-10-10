// -----------
// Tue, 10 Oct
// -----------

/*
local variables
global variables
class variables
class methods
RangeIterator
*/

/*
kinds of variables
    local
    global
    class
each is either static or non-static
*/

/*
local variables
    how many are there?
        one per function call
    what's the allocation time?
        on function entry
    what's the initialization time?
        at the statement
    what's the lifetime?
        lifetime of the function
    what's the scope?
        in the function, after the statement
*/

void f () {
    ...
    int i = g(...);
    ...}

/*
static local variables (compared to non-static, everything changed but scope)
    how many are there?
        one
    what's the allocation time?
        on program entry
    what's the initialization time?
        at the statement, only the first time
    what's the lifetime?
        lifetime of the program
    what's the scope?
        in the function, after the statement
*/

void f () {
    ...
    static int i = g(...);
    ...}

/*
global variables
    how many are there?
        one
    what's the allocation time?
        on program entry
    what's the initialization time?
        BEFORE main()
    what's the lifetime?
        lifetime of the program
    what's the scope?
        the program, with appropriate extern declarations in other files
*/

// foo.c++
int i = g(...);

void f () {
    ++i;}

// bar.c++
extern int i;

void h () {
    ++i;}

/*
static global variables (compared to non-static, nothing changed but scope)
    how many are there?
        one
    what's the allocation time?
        on program entry
    what's the initialization time?
        BEFORE main()
    what's the lifetime?
        lifetime of the program
    what's the scope?
        the file
*/

// foo.c++
static int i = g(...);

void f () {
    ++i;}

// bar.c++
static int i = g2(...);

void h () {
    ++i;}

/*
instance variables
    how many are there?
        one per instance
    what's the allocation time?
        on instance creation
    what's the initialization time?
        on instance creation
    what's the lifetime?
        lifetime of the instance
    what's the scope?
        dependent on the access directive
*/

template <typename T>
struct A {
    int i; // instance variable

    A () {
        i = g(...);}

    void f () { // instance method
        ++i;}}

void f () {
    cout << A<int>::i; // not ok

    A<int> x;
    A<int> y;
    A<int> z;
    cout << x.i;
    cout << (&x.i == &y.i); // false

    x.f();
    A* p = &x;
    p->f();

/*
access directives
    public:    anywhere
    private:   only the class and friends
    protected: the class and its descendents and friends

struct vs. class
    struct: the default is public
    class:  the default is private

convention
    if everything is public, use struct
    otherwise use class
*/

/*
friends
    who can make the declaration?
        a class
    whom can it be made about?
        another class/struct, a method, a function
    what privilege is granted with friendship?
        access to everything
    relationships
        it's not transitive
        is's not symmetric
*/

/*
class variables
    how many are there?
        one per template instantiation
    what's the allocation time?
        on instance creation
    what's the initialization time?
        on instance creation
    what's the lifetime?
        lifetime of the instance
    what's the scope?
        dependent on the access directive
*/

template <typename T>
struct A {
    int i;         // instance variable
    static int ci; // class    variable

    A () {
        i = g(...);

    void f () { // read/write instance method
        // special keyword 'this'
        // declaration of 'this':
            // A<T>* const this;
        cf();
//        ++i;
//        ++this->i;
        f2();
        this->f2();
        ++ci;
        f3();}

    void f2 ()
        {}

    void f3 () const { // read-only instance method
        ++i;           // not ok
        ++ci;
        cf();
        f();           // not ok

    static void cf () { // class method
        // declaration of 'this':
            // there is NO 'this'
        f();            // not ok
        ++i;            // not ok
        ++ci;};

void f () {
    cout << A<int>::i;
    A<int>::cf();

    A<int> x;
    A<int> y;
    A<int> z;
    cout << x.i;            // legal but misleading
    cout << x.cf();         // legal but misleading
    cout << (&x.i == &y.i); // true

    A<double> t;
    cout << (&x.i == &t.i); // false

    x.f();
    y.f();
    z.f();

    const A<int> cx;
    cx.f();          // not ok
    cx.cf();         // legal but misleading
