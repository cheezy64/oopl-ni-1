// -----------
// Tue, 31 Oct
// -----------

vector<int> x(10, 2);
...
// end up with size 20, capacity 40
{
vector<int> t(x); // S: 20; C: 20
x.swap(t);
}

// containment (C++'s stack)

template <typename T, typename C = deque<T>>
class stack {
    private:
        C _c;
    public:
        void push (const T& v) {
            _c.push_back(v);}

// inheritance (Java's stack)

template <typename T, typename C = deque<T>>
class stack : public C {
    private:
    public:
        void push (const T& v) {
            push_back(v);}

/*
two cases of reuse
    interface
    implementation

only implementation
    contains

both
    extends

only interface
    implements
*/

class Shape
    private:
        int _x;
        int _y;

    public:
        Shape& operator = (const Shape&) = default;

        void move (...) {...}

        double area () {return 0;}
    ...};

class Circle : public Shape
    private:
        int _r;

    public:
        double area () {return pi r**2;}

        int radius () {return _r;}

    ...};
