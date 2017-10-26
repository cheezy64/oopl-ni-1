// -----------
// Tue, 24 Oct
// -----------

int i = 2; // initialization

vs.

int i;
i = 2; // assignment

struct A {};

A()
A(A)
=(A)
~A()

/*
namespace std;

...

    namespace rel_ops;
    definitions for != based on ==
    definitions for >, <=, >= based on <
*/

#include <utility> // !=, >, <, <=

using namespace std;
using namespace std::rel_ops;

template <typename T>
class vector {
    friend bool operator == (const vector& lhs, const vector& rhs) {
        return (lhs.size() == rhs.size()) && equal(lhs.begin(), lhs.end(), rhs.begin());}

    friend bool operator < (const vector& lhs, const vector& rhs) {
        return lexigraphical_compare(...)

    private:
        ...

    public:
        ...};

T* a = new T[s];   // O(n), T(),  s times
fill(a, a + s, v); // O(n), =(T), s times

#include <memory> // allocator

allocator<T> x;

// four methods: allocate, construct, destroy, deallocate

T* a = x.allocate(s); // O(1), <nothing of T> // this is really malloc

for (int i = 0; i != s; ++i) // s times
    x.construct(a + i, v);   // T(T), once

...

for (int i = 0; i != s; ++i) // s times
    x.destroy(a + i);        // ~T(), once
x.deallocate(a, s);          // O(1), <nothing of T> // this is really free

new T[s]; // what exactly does this do? // allocate space and initialize with T()

// two steps

// step #1
void* a = operator new(s * sizeof(T)); // O(1), <nothing of T>

// step #2
for (int i = 0; i != s; ++i)
    (a + i)->T();            // pseudo code

#include <new> // in place new

new             T(v); // allocating memory for one T and invoking T(T)
new (<address>) T(v); // allocate nothing and invoke T(T) at <address>

delete [] a;

// two steps

// step #1
for (int i = 0; i != s; ++i)
    (a + i)->~T();

// step #2
operator delete(a)

template <typename T>
class Allocator {
    bool operator == (const Allocator& lhs, const Allocator& rhs) {
        return true;}

    public:
        T* allocate (int s) {
            return static_cast<T*>(operator new(s * sizeof(T)));}

        void construct (T* p, const T& v) {
            new (p) T(v);} // why not p->T(v)

        void destroy (T* p) {
            p->~T();}

        void deallocate (T* p, int) {
            operator delete(p);};

template <typename T>
class vector {
    private:
        allocator<T> a;
        T* _b;
        T* _e;

    public:
        // old one
        vector (int s, const T& v) {
            _b = new T[s];
            _e = _b + s;
            fill(_b, _e, v);}

        vector (int s, const T& v) :
                _a () {
            _b = _a.allocate(s); // O(1)
            _e = _b + s;
            for (int i = 0; i != s; ++i) // O(n)
                _a.construct(b + i, v);}   // O(1)

        // old one
        ~vector () {
            delete [] _b;}

        ~vector () {
            for (int i = 0; i != size(); ++i) // O(n)
                _a.destroy(_b + i);           // O(1)
            _a.deallocate(_b, size());}};

int main () {
    vector<int> x(10, 2);
