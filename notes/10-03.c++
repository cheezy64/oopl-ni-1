// -----------
// Tue, 03 Oct
// -----------

/*
casts
references
higher-order functions
fill()
iota()
accumulate()
*/

int* const a = new int[10];
++a; // not ok
delete [] a;

// in C
double  d;
double* p = &d;
int*    q = p;       // not ok
int*    q = (int*)p; // C cast

// in C++
const_cast
static_cast
reinterpret_cast
dynamic_cast

int  i = 2;
int& r;     // not ok
int& r = i; // most similar to is int* const

int       i  = 2;
const int cj = 3;

const int& s = cj;
const int& t = i;  // most similar to is const int* const

int a[5]; // undefined values

int* a = new int[5]; // undefined values

vector<int> x(5); // guaranteed to be 0

int multiplies (int x, int y) {
    return x * y;}

// there are functions that take functions as arguments
// higher-order functions

// assume f is such a higher-order function
f(multiplies);

// use a lambda instead
f([] (int x, int y) -> int {return x * y;});
