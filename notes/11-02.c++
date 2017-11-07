// -----------
// Thu,  2 Nov
// -----------

/*
refinement vs. replacement overriding

refinement
    constructors
    destructors
    operator = (), when auto-generated

replacement
    everything else
*/

x >> cout;      // output
y >> x >> cout; // too weird

Shape* p = new Circle(...);
Shape& r = *p;
r.move(...);
*p.move(...);   // not ok, because . has a higher precedence than *
(*p).move(...);
p->move(...);

Shape* p;
p = new Shape(...);
p->move(...);

if (...)
    p = new Circle(...)
else
    p = new Triangle(...);
p->move(...);

if (...)
    p = new Circle(...)
else
    p = new Triangle(...);
p->area(...);

struct A {
    void f (int) {...}

    void g (int) {...}

    void h (int) {...}};

struct B : A {
    using A::g;
    using A::h;

    void f (int) {...}

    void g (string) {...}

    void h (double) {...}};

int main () {
    B x;
    x.f(2);    // B::f

    x.g(2);    // not ok, made ok with using
    x.A::g(2);

    x.h(2);    // B::h, A::h with using

struct A {
    void f (int) {...}

    virtual g (int) {...}

    virtual h (int) {...}};

struct B : A {
    void f (int) {...}

    void g (int) {...}}; // the overriding method MUST have the same signature

struct C : B {
    ...};

int main () {
    B x;
    x.f(2);       // B::f // static binding
    x.g(2);       // B::g // static binding

    A* p = new B;
    p->f(2);      // A::f // static  binding
    p->g(2);      // B::g // dynamic binding something must be happening at runtime

    B* q = new C;
    q->g(2);      // dynamic binding

// compile time casts
const_cast
static_cast
reinterpret_cast

// runtime cast, only if virtual is present
dynamic_cast

struct A {
    virtual void f (int) {...};

struct B : A {
    void f (int) {...}};

struct C : A {
    void f (int) {...}};

int main () {
    A* p = nullptr;

    if (...)
        p = new B;
    else
        p = new C;

    p->f(2); // B::f or C::f; dynamic binding

/*
four cases where a virtual method will be statically bound

1. on an object
2. in a constructor
3. in a destructor
4. with the scope operator

in those four cases a virtual method could be inlined
*/
