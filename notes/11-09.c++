// -----------
// Thu,  9 Nov
// -----------

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
            delete _p;}

        double area () const {
            return _p->area();}};

int main () {
    Circle c(...);
    cout << c.area();

    Shape z = nullptr;

    Shape x = new Circle;
    cout << x.area();       // ?

    Shape y = new Triangle;
    cout << y.area();       // ?

    Shape z = y;
    z = x;

    vector<AbstractShape*> x(10, new Circle());

    {
    vector<Shape>          y(10, Shape(new Circle()));
    }

    vector<Shape>          z(10, new Circle());

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

        Shape2 (const Shape& rhs) :
            _p (rhs.p)
            {}

        Shape& operator = (Shape rhs) {
            swap(_p, rhs._p);
            return *this;}

        ~Shape () {
            delete _p;}

//        const AbstractShape& operator * () const {
//            return *_p;}

        AbstractShape& operator * () {
            return *_p;}

//        const AbstractShape* operator -> () const {
//            return _p;}

        AbstractShape* operator -> () {
            return _p;}

int main () {
    Shape z = nullptr;

    Shape x = new Circle;
    cout << (*x).area();    x.operator*().area()
    cout << x->area();      x.operator->()->area()

    Shape y = new Triangle;
    cout << y->area();

    Shape z = y;
    z = x;

    vector<Shape>          x(s, new Circle(...)); // eager with the copy
    vector<AbstractShape*> y(s, new Circle(...)); // not ok, lazy with the copy
    vector<Shape2>         z(s, new Circle(...)); // not ok, lazy with the copy

/*
    AS(), once
    C(), once
    S(), once
    V(), once
    S(S), s times
    AS(AS), s times
    C(C), s times
    ~S(), once
    ~C(), once
    ~AS(), once
*/

    x.push_back(new Triangle(...));
    ...

/*
    copy on write (cow)
*/

    Shape1 x = new Circle(...);
    Shape1 y = x;               // AS(AS), C(C)
    cout << x.get() == y.get(); // false

    Shape2 x = new Circle(...);
    Shape2 y = x;               // <nothing>
    cout << x.get() == y.get(); // true
    cout << x.area();
    cout << x.get() == y.get(); // true
    x.move(...);
    cout << x.get() == y.get(); // false

// look into items in the standard have a handle-like:

shared_ptr<T>
unique_ptr<T>
