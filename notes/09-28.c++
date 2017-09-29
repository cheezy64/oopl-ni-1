// -----------
// Thu, 28 Sep
// -----------

/*
equal()
&, * in the context of arguments
consts
*/

/*
good OO languages convert some runtime errors into compile time errors
*/

void f (int v) {
    ++v;}

int main () {
    int i = 2;
    f(i);
    cout << i; // 2



void g (int* p) {
    // ++p;       // legal, but dangerous later
    ++*p;}

int main () {
    int j = 2;
    g(j);      // not ok
    g(&j);
    cout << j; // 3
    g(185);    // not ok
    g(0);      // ok, but dangerous



void h (int& r) {
    ++*r;         // not ok
    ++r;}

int main () {
    int k = 2;
    h(&k);     // not ok
    h(k);
    cout << k; // 3
    h(185);    // not ok
    h(0);      // not ok



bool equal (int* b, int* e, int* x) {
    while (b < e) {
        if (*b != *x)
            return false;
        ++b;
        ++x;}
    return true;}

int a[] = {...};
int b[] = {...};
equal(a + 5, a + 10, b + 15);

/*
How many elements does a at least have to have? 10
How many elements does b at least have to have? 20
*/



template <typename T>
bool equal (T* b, T* e, T* x) {
    while (b < e) {
        if (*b != *x)
            return false;
        ++b;
        ++x;}
    return true;}

int a[] = {...};
int b[] = {...};
equal(a + 5, a + 10, b + 15); // T -> int

double a[] = {...};
double b[] = {...};
equal(a + 5, a + 10, b + 15); // T -> double



template <typename T1, typename T2>
bool equal (T1* b, T1* e, T2* x) {
    while (b < e) {
        if (*b != *x)
            return false;
        ++b;
        ++x;}
    return true;}

int    a[] = {...};
double b[] = {...};
equal(a + 5, a + 10, b + 15); // T1 -> int; T2 -> double



int  a[] = {2, 3, 4};
int* p   = a;
cout << *p; // 2
++p
cout << *p; // 3
++p;

list<int>           x = {2, 3, 4};
list<int>::iterator p = x.begin();
cout << *p; // 2
++p;
cout << *p; // 3
++p;



template <typename II1, typename II2>
bool equal (II1 b, II1 e, II2 x) {
    while (b != e) {
        if (*b != *x)
            return false;
        ++b;
        ++x;}
    return true;}

int a[] = {...};
int b[] = {...};
equal(a + 5, a + 10, b + 15); // T1 -> int*; T2 -> int*

double a[] = {...};
double b[] = {...};
equal(a + 5, a + 10, b + 15); // T1 -> double*; T2 -> double*

vector<int> y = {...};
equal(x.begin(), x.end(), y.begin()); // T1 -> list<int>::iterator; T2 -> vector<int>::iterator

/*
iterator categories

// input iterator
* (read only), ++, !=, ==

// output iterator
* (write only), ++ (loses == and !=)

// forward iterator
* (read write), ++, !=, ==

// bidirectional iterator
<forward iterator>, --

// random access iterator
<bidirectional iterator>, <, <=, >, >=, + (int), - (int), []
*/

/*
containers

vector           -> random access iterator
list             -> bidirectional iterator
forward_list     -> forward       iterator
ostream_iterator -> output        iterator
istream_iterator -> input         iterator
*/

/*
algorithms

equal   -> input         iterator
reverse -> bidirectional iterator
sort    -> random access iterator
*/

/*
consts
*/

int i;
i = 2;

const int ci = 3; // must be initialized

++i;
++ci; // not ok

int       i  = 2;
const int ci = 3;

int* p = &i; // read write pointer, many location (but can't point to consts)
++*p;
cout << i;   // 3

p = &ci; // not ok
++*p;



const int* pc; // read only pointer, many location (point to ANY int)
pc = &ci;
++pc;
++*pc; // not ok

pc = &i;
++*pc; // not ok

int* q = pc; // not ok

pc = p;

int       i  = 2
const int ci = 3;



int* const cq;       // not ok
int* const cq = &ci; // not ok
int* const cq = &i;  // read write pointer; one location pointer
++*cq;
++cq;                // not ok

int s;
cin >> s;
int a[s]; // not ok
++a;      // not ok

int* const a = new int[s];
++*a;
++a;                       // not ok
delete [] a;



int       i  = 2
const int ci = 3;

const int* const cpc;       // not ok
const int* const cpc = &ci; // read only pointer; one location
++cpc;                      // not ok
++*cpc;                     // not ok
