// -----------
// StrCmp1.c++
// -----------

// http://en.cppreference.com/w/c/string/byte/strcmp

#include <cassert>  // assert
#include <iostream> // cout, endl

using namespace std;

int my_strcmp (const char* a, const char* b) {
    while ((*a != 0) && (*a == *b)) {
        ++a;
        ++b;}
    return *a - *b;}

int main () {
    cout << "StrCmp1.c++" << endl;

    assert(my_strcmp("",    "")    ==  0);
    assert(my_strcmp("abc", "abc") ==  0);
    assert(my_strcmp("abc", "abb") == 'c' - 'b');
    assert(my_strcmp("abc", "ab")  == 'c' -  0);
    assert(my_strcmp("ab",  "abc") ==  0  - 'c');

    cout << "Done." << endl;
    return 0;}
