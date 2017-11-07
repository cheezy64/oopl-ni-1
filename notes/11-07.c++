// -----------
// Tue,  7 Nov
// -----------

struct A {
    virtual void f (int) {...}};

struct B : A {
    void f (int) {...}};

int main () {
    A* p = new B;
    p->f(2);      // B::f

/*
five properties in a signature
    return type is covariant
    name
    number of args
    types of args
    const or not
*/

class Triangle : public Shape {
    public:
        Triangle (...) : ... {...}

int main () {
    Triangle x;
    cout << x.area(); // 0

struct A {};
struct B : A {};

/*
only change the behavior of B objects, what do I edit?
    B

change the behavior of A AND B object, what do I edit
    A

only change the behavior of A objects, what do I edit?
    can't do it
*/

struct A' {...};     // want this to be abstract class
struct A : A' {};    // concrete class
struct B : A' {...}; // concrete class

/*
motivation for an abstract method (pure virtual method)

1. overriding is brittle

2. would like to compel children sometimes to override a method

3. desire for an abstract class
*/

struct A {
    virtual void f (int) = 0; // pure virtual method
    virtual void g (int);};

void A::g (int) {
    ...}

struct B : A {
    };

struct C : A {
    void f (int) {...}};

int main () {
    A x;          // not ok
    A* p = new A; // not ok
    A* q = new B; // not ok
    A* r = new C;
    r->g(2);

/*
what are the consequences of declaring a METHOD to be pure virtual

1. its class becomes ABSTRACT

2. children MUST override or become ABSTRACT

3. definition becomes OPTIONAL
*/

struct A {
    virtual ~A() = 0;};

A::~A() {...}

/*
what are the consequences of declaring a DESTRUCTOR to be pure virtual

1. its class becomes ABSTRACT

2. does not hold

3. does not hold
*/

struct A {
    virtual A* clone () const = 0;

struct B : A {
    virtual B* clone () const {
        return new B(*this);}};

struct C : A {
    virtual C* clone () const {
        return new C(*this);}};

int main () {
    A* p;
    if (...)
        p = new B;
    else
        p = new C;

    A* q = <somehow be a new ? that is a copy of the ? pointed to by p>
    A* q = p->clone();

    B* r = new B;
    B* s = r->clone();

/*
exercise

1. rename Shape to AbstractShape
2. define clone
3. make area abstract and don't define it
4. make equals abstract and define it
*/

struct A {
    virtual void f (int) final {...}
    virtual void g (int) {...} // worth avoiding
    virtual void h (int) = 0;

struct B : A {
    void g (int) override {...}
    void h (int) {...}};

/*
what does A convey to its children about f()?
    it's optional for the child to define f()
    definition in the child is somewhat unattractive
    because it'll be called on a child object,
    but not on a parent pointer to a child object

what does A convey to its children about g()?
    it's optional for the child to define g()
    correctly gets called on a child object
    and on a parent pointer to a child object
    but if parent or child change signature, it's brittle

what does A convey to its children about h()?
    it's required for the child to define h()
    if parent or child change signature, it doesn't compile
*/

struct A {
    A (int) {...}};

struct B : A {};

struct C : A {}};

int main () {
    A v(2);
    vector<A> x(10, v); // homogeneous

    B w(3);
    vector<B> y(20, w); // homogeneous

    vector<A> z(30, w); // homogeneous

    vector<A*> t(40, w);     // not ok
    vector<A*> t(40, &w);    // not ok
    vector<A*> t(40, new B); // not ok

    {
    vector<A*> t;
    for (int i = 0; i != 40; ++i)
        t.push_back(new B);
    t.push_back(new C);
    <work>
    } // memory leak

    {
    vector<AbstractShape*> x;
    x.push_back(new Circle(...));
    x.push_back(new Triangle(...));
    <work>
    } memory leak

class Shape {
    private:
        AbstractShape* _p;

    public:
        Shape (AbstractShape* p) :
            _p (p)
            {}

        Shape (const Shape& rhs) :
            _p (rhs._p->clone())
            {}

        Shape& operator = (Shape rhs) {
            swap(_p, rhs._p);
            return *this;}

        ~Shape () {
            delete _p;}};

int main () {
    Shape x = new Circle;
    Shape y = new Triangle;

    Shape z = y;
    z = x;

    vector<AbstractShape*> x(10, new Circle());

    {
    vector<Shape>          y(10, Shape(new Circle()));
    }

    vector<Shape>          z(10, new Circle());
