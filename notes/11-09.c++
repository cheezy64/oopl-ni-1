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

        Shape& operator = (Shape rhs) {
            swap(_p, rhs._p);
            return *this;}

        ~Shape () {
            delete _p;}

        const AbstractShape& operator * () const {
            return *_p;}

        AbstractShape& operator * () {
            return *_p;}

        const AbstractShape* operator -> () const {
            return _p;}

        AbstractShape* operator -> () const {
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
