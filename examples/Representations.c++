// -------------------
// Representations.c++
// -------------------

#include <cassert>  // assert
#include <climits>  // INT_MAX, INT_MIN
#include <cmath>    // log, sqrt
#include <iostream> // cout, endl, hex, oct
#include <sstream>  // ostringstream
#include <string>   // ==

int main () {
    using namespace std;
    cout << "Representations.c++" << endl;

    {
    const int i = 2;
    assert(i == 2);
    assert(i == 02);                                // 00 000 000 000 000 000 000 000 000 000 010
    assert(i == 0x2);                               // 0000 0000 0000 0000 0000 0000 0000 0010
    ostringstream out;
    out << i << " " << oct << i << " " << hex << i;
    assert(out.str() == "2 2 2");
    }

    {
    const int i = 17;
    assert(i == 17);
    assert(i == 021);                               // 00 000 000 000 000 000 000 000 000 010 001
    assert(i == 0x11);                              // 0000 0000 0000 0000 0000 0000 0001 0001
    ostringstream out;
    out << i << " " << oct << i << " " << hex << i;
    assert(out.str() == "17 21 11");
    }

    {
    const int i = -2;
    ostringstream out;
    assert(i == -2);
    assert(i == -02);                               // 11 111 111 111 111 111 111 111 111 111 110
    assert(i == -0x2);                              // 1111 1111 1111 1111 1111 1111 1111 1110
    out << i << " " << oct << i << " " << hex << i;
    assert(out.str() == "-2 37777777776 fffffffe");
    }

    {
    const int i = 2;
    const int j = ~i + 1;
    assert(i ==  2);      // 0000 0000 0000 0000 0000 0000 0000 0010
    assert(j == -2);      // 1111 1111 1111 1111 1111 1111 1111 1110
    }

    {
    const int i = 2;
    const int j = i << 3;
    assert(i ==  2);       // 0000 0000 0000 0000 0000 0000 0000 0010
    assert(j == 16);       // 0000 0000 0000 0000 0000 0000 0001 0000
    const int k = j >>  3;
    assert(j == 16);       // 0000 0000 0000 0000 0000 0000 0001 0000
    assert(k ==  2);       // 0000 0000 0000 0000 0000 0000 0000 0010
    }

    {
    const int i = -2;
    const int j = i << 3;
    assert(i ==  -2);      // 1111 1111 1111 1111 1111 1111 1111 1110
    assert(j == -16);      // 1111 1111 1111 1111 1111 1111 1111 0000
    const int k = j >>  3;
    assert(j == -16);      // 1111 1111 1111 1111 1111 1111 1111 0000
    assert(k ==  -2);      // 1111 1111 1111 1111 1111 1111 1111 1110
    }

    {
    short i = 1;
    while (i > 0)
        ++i;
    assert(i == SHRT_MIN);
    assert(i == -32768);
    assert(i == static_cast<short>(0100000));       // 1 000 000 000 000 000
    assert(i == static_cast<short>(0x8000));        // 1000 0000 0000 0000
    ostringstream out;
    out << i << " " << oct << i << " " << hex << i;
    assert(out.str() == "-32768 100000 8000");
    }

    {
    int i = INT_MAX;
    ++i;
    assert(i == INT_MIN);
    assert(i == -2147483647 - 1);
    assert(i == static_cast<int>(020000000000));             // 10 000 000 000 000 000 000 000 000 000 000
    assert(i == static_cast<int>(0x80000000));               // 1000 0000 0000 0000 0000 0000 0000 0000
    ostringstream out;
    out << i << " " << oct << i << " " << hex << i;
    assert(out.str() == "-2147483648 20000000000 80000000");
    }

    {
    int i = INT_MIN;
    --i;
    assert(i == INT_MAX);
    assert(i == 2147483647);
    assert(i == static_cast<int>(017777777777));             // 01 111 111 111 111 111 111 111 111 111 111
    assert(i == static_cast<int>(0x7fffffff));               // 0111 1111 1111 1111 1111 1111 1111 1111
    ostringstream out;
    out << i << " " << oct << i << " " << hex << i;
    assert(out.str() == "2147483647 17777777777 7fffffff");
    }

    {
//  int i = 1 / 0; // warning: division by zero in ‘1 / 0’
    }

    assert(sizeof(int) == sizeof(float));

    {
    union U {
        float f;
        int   i;};
    U x;
    x.f = 2;
    ostringstream out;
    out << x.f << " " << x.i << " " << oct << x.i << " " << hex << x.i;
    assert(out.str() == "2 1073741824 10000000000 40000000");
    }

    {
    float f = 2;
    int   i = *(reinterpret_cast<int*>(&f));                      // sign: 0, exponent: 1+127=128, mantissa: 1.0
    ostringstream out;
    out << f << " " << i << " " << oct << i << " " << hex << i;
    assert(out.str() == "2 1073741824 10000000000 40000000");
    }

    {
    float f = 2;
    int   i = reinterpret_cast<int&>(f);                          // sign: 0, exponent: 1+127=128, mantissa: 1.0
    ostringstream out;
    out << f << " " << i << " " << oct << i << " " << hex << i;
    assert(out.str() == "2 1073741824 10000000000 40000000");
    }

    {
    float f = -2;
    int   i = *(reinterpret_cast<int*>(&f));                      // sign: 1, exponent: 1+127=128, mantissa: 1.0
    ostringstream out;
    out << f << " " << i << " " << oct << i << " " << hex << i;
    assert(out.str() == "-2 -1073741824 30000000000 c0000000");
    }

    {
    float f = 2.5f;
    int   i = *(reinterpret_cast<int*>(&f));                      // sign: 0, exponent: 1+127=128, mantissa: 1.01
    ostringstream out;
    out << f << " " << i << " " << oct << i << " " << hex << i;
    assert(out.str() == "2.5 1075838976 10010000000 40200000");
    }

    {
    float f = -2.5f;
    int   i = *(reinterpret_cast<int*>(&f));                      // sign: 1, exponent: 1+127=128, mantissa: 1.01
    ostringstream out;
    out << f << " " << i << " " << oct << i << " " << hex << i;
    assert(out.str() == "-2.5 -1071644672 30010000000 c0200000");
    }

    {
    float f = 1.0 / 0;                                            // warning: division by zero in "1.0e+0 / 0"
    int   i = *(reinterpret_cast<int*>(&f));                      // sign: 0, exponent: 255, mantissa: 1.0
    ostringstream out;
    out << f << " " << i << " " << oct << i << " " << hex << i;
    assert(out.str() == "inf 2139095040 17740000000 7f800000");
    }

    {
    float f = log(0);
    int   i = *(reinterpret_cast<int*>(&f));                      // sign: 1, exponent: 255, mantissa: 1.0
    ostringstream out;
    out << f << " " << i << " " << oct << i << " " << hex << i;
    assert(out.str() == "-inf -8388608 37740000000 ff800000");
    }

    {
    float f = sqrt(-1);
    int   i = *(reinterpret_cast<int*>(&f));                      // sign: 0, exponent: 255, mantissa: 1.1
    ostringstream out;
    out << f << " " << i << " " << oct << i << " " << hex << i;
    #ifdef __APPLE__
        assert(out.str() ==  "nan -4194304 37760000000 ffc00000");
    #else
        assert(out.str() == "-nan -4194304 37760000000 ffc00000");
    #endif
    }

    cout << "Done." << endl;
    return 0;}
