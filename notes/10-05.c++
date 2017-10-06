// -----------
// Thu, 05 Oct
// -----------

/*
cache
returns
copy()
transform()
reverse()
selection
iteration
classes
*/

const int* a = "abc";
const int* b = a;
cout << (a == b); // true

for (int i = 0; i != 10; ++i)
    s += i;

{
int i = 0;
while (i != 10) {
    s += i;
    ++i;}
}

for (int v : a) {
    s += v;}

? b = begin(a);
? e = end(a);
while (b != e) {
    int v = *b;
    s += v;
    ++b;}

template <typename T>
struct A {
    int    i;
    double d;
    T      t;};

int main () {
    {
    A<T> x;    // default constructor
               // i and d will NOT be initialized
               // for T a built-in type, t will NOT be initialized
               // for T a user     type, t will be default constructed
    A<T> y(x); // copy constructor
               // i and d will be assigned the corresponding value
               // for T a built-in type, t will be assigned the corresponding value
               // for T a user     type, t will be copy constructed
    y = x;     // copy assignment operator
               // i and d will be assigned the corresponding value
               // for T a built-in type, t will be assigned the corresponding value
               // for T a user     type, t will be copy assigned
    }          // destructor
               // nothing happens to i and d
               // for T a built-in type, t nothing happens to t
               // for T a user     type, t will be destructed

template <typename T>
class A {
    public:
        int    i;
        int*   q;
        static T j;
    private:
        double d;
        T      t;
    public:
        int f (int k) {
            ???}};

int main () {
    A<T> x;
    x.i = 2;
    x.d = 3.4; // not ok

    int j = x.f(2);

    A<T>* p = &x;
    (*p).i = 3;
    p->i = 3;
    int k = (*p).f(2);
    int m = p->f(2);

    p->q = &k;

/*
5 A<int>
10 A<double>
15 A<Elephant>
*/
