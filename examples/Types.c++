// ---------
// Types.c++
// ---------

// http://en.cppreference.com/w/cpp/language/types

#include <cassert>       // assert
#include <deque>         // deque
#include <iostream>      // cout, endl
#include <list>          // list
#include <map>           // map
#include <queue>         // priority_queue, queue
#include <set>           // set
#include <stack>         // stack
#include <unordered_map> // unordered_map
#include <unordered_set> // unordered_set
#include <vector>        // vector

using namespace std;

template <typename T>
struct A {
    int    i;
    double d;
    T      x;};

void test () {
    bool b = true;
    assert(sizeof(b) ==  1);

    char c = 'a';
    assert(sizeof(c) ==  1);

    short s = 2;
    assert(sizeof(s) ==  2);

    int i = 2;
    assert(sizeof(i) ==  4);

    long l = 2L;
    assert(sizeof(l) ==  8);

    long long ll = 2LL;
    assert(sizeof(ll) ==  8);

    float f = 2.34F;
    assert(sizeof(f) == 4);

    double d = 2.34;
    assert(sizeof(d) == 8);

    long double ld = 2.34L;
    assert(sizeof(ld) == 16);

    {
    char a[] = "abc";
    assert(sizeof(a) == 4 * sizeof(char));
    }

    {
    int a[] = {2, 3, 4};
    assert(sizeof(a) == 3 * sizeof(int));
    }

    {
    vector<int> x;             // front loaded array
    assert(x.size() == 0);
    vector<int> y(10, 2);
    assert(y.size() == 10);
    vector<int> z = {2, 3, 4};
    assert(z.size() == 3);
    }

    {
    list<int> x;             // doubly linked list
    assert(x.size() == 0);
    list<int> y(10, 2);
    assert(y.size() == 10);
    list<int> z = {2, 3, 4};
    assert(z.size() == 3);
    }

    {
    deque<int> x;             // middle loaded array of arrays
    assert(x.size() == 0);
    deque<int> y(10, 2);
    assert(y.size() == 10);
    deque<int> z = {2, 3, 4};
    assert(z.size() == 3);
    }

    {
    stack<int> x;          // LIFO backed by a vector, list, or deque
    assert(x.size() == 0);
    }

    {
    queue<int> x;          // FIFO backed by a list or deque
    assert(x.size() == 0);
    }

    {
    priority_queue<int> x; // binary heap backed by a vector or deque
    assert(x.size() == 0);
    }

    {
    set<int> x = {2, 3, 4}; // red-black binary search tree
    assert(x.size() == 3);
    }

    {
    unordered_set<int> x = {2, 3, 4}; // hash table
    assert(x.size() == 3);
    }

    {
    map<char, int> x = {{'a', 2}, {'b', 3}, {'c', 4}}; // red-black binary search tree
    assert(x.size() == 3);
    }

    {
    unordered_map<char, int> x = {{'a', 2}, {'b', 3}, {'c', 4}}; // hash table
    assert(x.size() == 3);
    }

    {
    A<int> x = {2, 3.45, 6};
    assert(sizeof(x) == 24);
    }

    {
    A<double> x = {2, 3.45, 6.78};
    assert(sizeof(x) == 24);
    }

    {
    A< A<int> > x = {2, 3.45, {2, 3.45, 6}};
    assert(sizeof(x) == 40);
    }}

int main () {
    cout << "Types.c++" << endl;
    test();
    cout << "Done." << endl;
    return 0;}
