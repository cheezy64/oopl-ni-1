// -----------
// Tue, 17 Oct
// -----------

/*
arrays
vectors
*/

int       a[] = {2, 3, 4}; // int* const a
const int a[] = {2, 3, 4}; // const int* const a

T a[s] = {2, 3, 4}; // T(int), 3 times; T(), (s - 3) times

T a[s]; // T(), s times

T a[s] = {}; // T(), s times

T x = ...;
T y = x;
y = x;

int s;
cin >> s;

int a[s]; // not ok

int* a = new int[s]; // malloc won't invoke a constructor
a[0] = 2;
++a;
delete [] a;         // free won't invoke a destructor

int* const a = new int[s]; // malloc won't invoke a constructor
a[0] = 2;
++a;                       // not ok
delete [] a;               // free won't invoke a destructor

int* const a = new int[s]; // O(1), no initialization
...
delete    a;               // undefined
delete [] a;

T*   const a = new T[s]; // O(n), T(), s times
...
delete    a;             // O(1), ~T(), once
delete [] a;             // O(n), ~T(), s times

const int* a = ...;
int*       b = a;   // not ok

int* const a = ...;
int*       b = a;   // ok

const int i = ...;
int       j = i;    // ok

Mammal x;
Tiger  y;

Mammal* p = &x;
p = &y;         // not ok

Tiger* q = &y;
q = &x;         // ok

T* a = new T[s];   // T(),  s times
fill(a, a + s, v); // =(T), s times

T* b = new T[s];   // T(),  s times
copy(a, a + s, b); // =(T), s times

copy(a, a + s, b); // =(T), s times

delete [] a;       // ~T(), s times
delete [] b;       // ~T(), s times

vector<T> x(s, v); // T(T), s times

vector<T> y = x;   // T(T), s times

y = x;             // =(T), s times

vector<T> x(10, v);
vector<T> y(20, w);

x = y; // ~T(), 10 times; T(T), 20 times

vector<T> x(10, v);
vector<T> y(20, w);

y = x; // ~T() 10 times; T(T), 10 times

template <typename T>
class vector {
    public:
        typedef T* iterator;
        using iterator = T*; // C++11

        const T& operator [] (...) const {
            ...}

        T& operator [] (...) {
            ...}

int main () {
    vector<int> x(10, 2);
    cout << x[0];         // x.operator[](0)
    x[0] = 3;

    const vector<int> y(20, 3);
    cout << y[0];               // ok
    y[0] = 3;                   // not ok
