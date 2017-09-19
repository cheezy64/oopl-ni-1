// ---------
// Hello.c++
// ---------

// http://en.cppreference.com/w/

#include <iostream> // cout, endl

int main () {
    using namespace std;
    cout << "Nothing to be done." << endl;
    return 0;}

/*
Developed in 1978 by Bjarne Stroustrup of Denmark.
C++ is procedural, object-oriented, statically typed, and not garbage collected.



% which g++
/usr/bin/g++



% g++ --version
g++  (Ubuntu 5.4.0-6ubuntu1~16.04.4) 5.4.0 20160609
Copyright (C) 2015 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.



% g++ -pedantic -std=c++14 -Wall -Weffc++ Hello.c++ -o Hello



% ./Hello
Nothing to be done.
*/
