// -----------
// Thu, 19 Oct
// -----------

/*
vectors
    copying    them
    assignment them
*/

int i; // declaration
i = 2; // assignment

int i = 2; // initialization

A x;
A y = x; // the same as A y(x);
y = x;

template <typename T>
class vector {
    private:
        int _s;
        T*  _a;
    public:
        vector (const vector& rhs) {  // auto generated incorrect implementation
            _s = rhs._s;
            _a = rhs._a;}

        vector (const vector& rhs) { // reuse #1, not that nice
            _a    = nullptr;
            *this = rhs;}

        vector (const vector& rhs) {
            _s = rhs._s;
            _a = new T[_s];                 // O(n)
            copy(rhs._a, rhs._a + _s, _a);} // O(n)

        vector& operator = (vector rhs) { // reuse #2, very elegant
            swap(_s, rhs._s);
            swap(_a, rhs._a);
            return *this;}

        vector& operator = (const vector& rhs) {
            if (this  == rhs)  // not ok
            if (*this == rhs)  // content  comparison, don't want
            if (this  == &rhs) // identity comparison, do    want
                return *this;
            _s = rhs._s;
            delete [] _a;
            _a = new T[_s];                // O(n)
            copy(rhs._a, rhs._a + _s, _a); // O(n)
            return *this;}

        vector& operator = (const vector& rhs) { // auto generated incorrect implementation
            _s = rhs._s;
            _a = rhs._a;
            return *this;}

        ~vector () {
            delete [] _a;}

void f (vector<int> z) {}

int main () {
    vector<int> x(10, 2);
    vector<int> y(20, 3);
    x = y;                // x.operator=(y)
    vector<int> z = x;
    f(x);
    x = x;

template <typename T>
class vector {
    friend bool operator == (const vector& lhs, const vector& rhs) {
        if (lhs.size() != rhs.size())
            return false
        return equal(lhs.begin(), lhs.end(), rhs.begin());} // begin(x) -> x.begin()

    private:
        int _s;
        T*  _a;

    public:
        vector (const vector& rhs) :
            _s (rhs._s),
            _a ((_s == 0) ? nullptr : new T[_s])
            {}

vector<int> f () {
    vector<int> x(...);
    ...
    return x;}

int main () {
    ...
    vector<int> y = f();
    ...

struct A {};

struct A {
    A () {} // default constructor

    A (const A&) {} // copy constructor

    A (A&&) {} // move constructor

    A& operator = (const A&) {} // copy assignment operator

    A& operator = (A&&) {} // move assignment operator

    ~A () {}}; // destructor
