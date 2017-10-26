// -----------
// Thu, 26 Oct
// -----------

int i = 2; // initialization
int i(2);

int i;
i = 2; // assignment

template <typename T>
class vector {
    private:
        ...
    public:
        vector () {...}
        vector (int s) {...}
        vector (int s, const T& v) {...}

        vector (int s = 0, const T& v = T()) {...}

void f (int) {...}
void f (int) {...} // not ok

/*
overloading rules
    member
        function
            const, number, type

        operator
            const type

    non-member
        function
            number, type

        operator
            type
*/

// policy design pattern

template <typename T, typename A = allocator<T>>
class vector {
    private:
        A  _a;
        T* _b;
        T* _e;

    public:
        vector (int s, const T& v, const A& a = A())
                _a (a) {
            _b = _a.allocate(s);         // O(1)
            _e = _b + s;
            for (int i = 0; i != s; ++i) // O(n)
                _a.construct(b + i, v);} // O(1)

        ~vector () {
            for (int i = 0; i != size(); ++i) // O(n)
                _a.destroy(_b + i);           // O(1)
            _a.deallocate(_b, size());}};     // O(1)

int main () {
    vector<int>                 x(10, 2);
    vector<int, allocator<int>> y(10, 2);

    my_allocator<int> a;                     // not ok
    vector<int, my_allocator<int>> z(10, 2); // not ok

    my_allocator<int> a(...);
    vector<int, my_allocator<int>> z(10, 2, a);

/*
container adapter

stack can be backed
    vector
    deque (default)
    list

queue can be backed
    deque (default)
    list

priority_queue can be backed
    vector (deque)
    deque
*/

template <typename T, typename C = deque<T>>
class stack {
    private:
        C _c;

    public:
        stack (const C& c = C()) :
            _c (c)
            {}
        ...};

stack<int> x;
stack<int, list<int>> y;

my_container<int> c;             // not ok
stack<int, my_container<int>> z; // not ok

my_container<int> c(...);
stack<int, my_container<int>> z(c);

/*
iterator concepts

input
output
forward
bidirectional
random access
*/

vector (int s, const T& v, const A& a = A())
        _a (a) {
    _b = _a.allocate(s);         // O(1)
    _e = _b + s;
    for (int i = 0; i != s; ++i) // O(n)
        _a.construct(b + i, v);} // O(1)

template <typename A, typename FI, typename T>
void my_uninitialized_fill (const A& a, FI b, FI e, const T& v) {
    FI p = b;
    try {
        while (b != e) {
            a.construct(&*b, v);
            ++b;}
    catch (...) {
        while (p != b) {
            --b;
            a.destroy(&*b);}
        throw;}}
