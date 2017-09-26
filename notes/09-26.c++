// -----------
// Tue, 26 Sep
// -----------

/*
exceptions
types

finish overviewing the types
casting
&, *
*/

int i = 2;
int j = ++i;
cout << i;   // 3
cout << j;   // 3
++i = j;     // not ok in C, Java; ok in C++

int i = 2;
int j = i++;
cout << i;   // 3
cout << j;   // 2
i++ = j;     // not ok

(i + j) = k; // not ok

I i;
++i; // faster
i++; // for built-in types, only, compiler we'll rewrite as ++i

++++i;

/*
vector is a front-loaded array
cost of adding is:
    at the back:   O(1), amortized
    at the front:  O(n), push_front is NOT available
    anywhere else: O(n)
cost of removing:
    at the back:   O(1)
    at the front:  O(n), pop_front is NOT available
    anywhere else: O(n)
cost of indexing:
    O(1)

list is a doubly-linked list
cost of adding is:
    O(1)
cost of removing:
    O(1)
cost of indexing:
    O(n), [] NOT available
*/

list<int> x(...);
list<int>::iterator b = x.begin();
list<int>::iterator e = x.end();
cout << *b; // first element
++b;
cout << *b; // second element
++b;
...
// eventually b == e, and we're done

while (b != e) {
    cout << *b;
    ++b;}

vector<int> x(...);
vector<int>::iterator b = x.begin();
x.push_back(...); // many times

/*
when vector resizes, iterators, pointers, and references can be invalidated
*/

/*
deque is a middle-loaded array of arrays
cost of adding is:
    at the front or the back: O(1), amortized
    anywhere else:            O(n)
cost of removing:
    at the front or the back: O(1)
    anywhere else:            O(n)
cost of indexing:
    O(1), but more expensive than vector
    because of an additional, add, divide, and mod
*/

/*
three workhorse containers: vector, list, deque
*/

/*
container adapters: stack, queue, priority_queue
*/

/*
stack: LIFO
    back with vector, list, deque; default deque
    push -> push_back
    pop  -> pop_back
*/

/*
queue: FIFO
    back with list, deque; default deque
    push -> push_back
    pop  -> pop_front
*/

/*
priority_queue:
    back with vector, deque; default vector
    push -> push_back
    pop  -> pop_front
*/

cout << "hi" << endl;
cout << "hi" << flush;
cout << oct;

float f = 2.3;
int* p  = (int*)(&f);

const_cast
static_cast
reinterpret_cast
dynamic_cast

/*
two tokens
    *, &
two contexts
    applied to a typename
    applied to a variable
*/

int i = 2;
int v = i;
++v;
cout << i; // 2
cout << v; // 3

int  i = 2;
int* p = i;  // not ok
int* p = &i; // & can only be applied to an l-value
++p;         // ok; dangerous
++*2;        // not ok
++*i;        // not ok
++*p;        // * can only be applied to a pointer

int  i = 2;
int& r = &i; // not ok
int& r = i;  // r and i become permanent aliases of each other
