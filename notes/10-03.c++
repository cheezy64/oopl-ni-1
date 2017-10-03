// -----------
// Tue, 03 Oct
// -----------

/*
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
















