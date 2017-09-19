/*
1. name
2. how much C++ or something similar
3. why are you taking class now
4. what do you do here

// is the line commment

/*
    is the block comment
*/

/*
full names are <namespace name>::<symbol name>
example: std::cout
using is a scoped statement

cout is an ostream
*/

int i = 2;
int j = 3;
int k = (i << j); // left shift

cout << i; // output

/*
operator overloading
<< is defined on int, on ostream, NOT on float

you can't overload on a built-in type
you can't invent an operator?
*/

struct A {
    int i;
}; // has no built in operators with a few special exceptions

/*
&: address of,    is     overloadable, but very unusual
.: member access, is not overloadable
*/

int main () {
    A x;          // on the stack
    A* r = new A; // on the heap

    A* p = &x; // address of
    x.i = 2;   // member access

    int j;            // on the stack
    int* q = new int; // on the heap

    cout << i;      // output int i
    cout << i << j; // output int i and int j

    cout << flush; // flush the buffer
    cout << "\n";  // new line
    cout << endl;  // new line and flush the buffer

/*
Collatz Conjecture (1930s)

take a pos int
if even, divide by 2
otherwise, multiply by 3 and add 1
repeat until 1

5 16 8 4 2 1
the cycle of  5 is 6
the cycle of 10 is 7

assertions are not good
    for testing
    for user errors

demo an obvious fact: bad tests can hide bad code

0. run the code, and it succeeds
1. identify the bad tests
2. fix the tests
3. run the code, and it fails
4. identify the bad code
5. fix the code
6. run the code, and it succeeds
*/

int i = 2;
int j = ++i; // pre-increment, no copy
cout << i;   // 3
cout << j;   // 3

int i = 2;
int j = i++; // post-increment, copy
cout << i;   // 3
cout << j;   // 2

for (int i = 0; i != s; i++)
    ...

{
int i = 0;
while (i != s) {
    ...
    i++;}        // compiler will change i++ to ++i
}

{
I i = 0;         // user-defined type
while (i != s) {
    ...
    i++;}        // compiler can NOT change i++ to ++i
}

// always prefer pre-increment

int i = 2;
int j = 3;
int k = (2 + 3);
(2 + 3);     // not ok, + is an expression
(2 + 3) = 4; // not ok, + returns an r-value

/*
l-value can     be on the lhs of an assignment (e.g. i, j, not 2, 3)
r-value can NOT be on the lhs of an assignment (e.g. 2, 3)

+ takes two r-values
+ is an expression
+ returns an r-value
*/

i += 3;
j  = (i += 3);
(i += j) = 4;  // not ok in Java, not ok in C, ok in C++

/*
+= takes an l-value and an r-value
+= is a statement and an expression
+= returns an l-value
*/

k = i++;
i++ = 2; // not ok

j   = ++i;
++i = 2;   // not ok in C, not ok in Java, ok in C++

/*
post-increment takes an l-value, returns an r-value
pre-increment  takes an l-value, returns an l-value
*/

i++++; // not ok
++++i; // not ok in C, not ok in Java, ok in C++
