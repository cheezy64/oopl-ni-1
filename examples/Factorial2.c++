// --------------
// Factorial2.c++
// --------------

#include <ctime>      // clock, clock_t, CLOCKS_PER_SEC
#include <functional> // function, multiplies
#include <iomanip>    // setprecision, setw
#include <iostream>   // cout, endl
#include <numeric>    // accumulate, iota
#include <vector>     // vector

#include "gtest/gtest.h"

using namespace std;

// recursive procedure
// linear recursive process
int factorial_recursion (int n) {
    assert(n >= 0);
    if (n < 2)
        return 1;
    return n * factorial_recursion(n - 1);}

int factorial_tail_recursion_aux (int n, int m) {
    assert(n >= 0);
    assert(m >= 1);
    if (n < 2)
        return m;
    return factorial_tail_recursion_aux(n - 1, n * m);}

// recursive procedure
// linear iterative process
int factorial_tail_recursion (int n) {
    assert(n >= 0);
    return factorial_tail_recursion_aux(n, 1);}

// iterative procedure
// linear iterative process
int factorial_iteration (int n) {
    assert(n >= 0);
    int v = 1;
    while (n > 1) {
        v *= n;
        --n;}
    return v;}

// iterative procedure
// linear iterative process
int factorial_accumulate (int n) {
    assert(n >= 0);
    vector<int> x(n);
    iota(x.begin(), x.end(), 1);
    const int v = accumulate(x.begin(), x.end(), 1, multiplies<int>());
    return v;}

using testing::TestWithParam;
using testing::Values;

using Factorial_Signature = function<int (int)>;

struct Factorial_Fixture : TestWithParam<Factorial_Signature> {};

INSTANTIATE_TEST_CASE_P(
    Factorial_Instantiation,
    Factorial_Fixture,
    Values(
        factorial_recursion,
        factorial_tail_recursion,
        factorial_iteration,
        factorial_accumulate));

TEST_P(Factorial_Fixture, test_0) {
	ASSERT_EQ(GetParam()(0), 1);}

TEST_P(Factorial_Fixture, test_1) {
	ASSERT_EQ(GetParam()(1), 1);}

TEST_P(Factorial_Fixture, test_2) {
	ASSERT_EQ(GetParam()(2), 2);}

TEST_P(Factorial_Fixture, test_3) {
	ASSERT_EQ(GetParam()(3), 6);}

TEST_P(Factorial_Fixture, test_4) {
	ASSERT_EQ(GetParam()(4), 24);}

TEST_P(Factorial_Fixture, test_5) {
	ASSERT_EQ(GetParam()(5), 120);}

TEST_P(Factorial_Fixture, test_6) {
    const clock_t b = clock();
    for (int i = 0; i != 1000; ++i)
        GetParam()(12);
    const clock_t e = clock();
    cout << fixed << setprecision(3) << setw(5);
    cout << ((e - b) * 1000.0 / CLOCKS_PER_SEC) << " milliseconds" << endl;
    cout << endl;}

/*
% Factorial2
Running main() from gtest_main.cc
[==========] Running 28 tests from 1 test case.
[----------] Global test environment set-up.
[----------] 28 tests from Factorial_Instantiation/Factorial_Fixture
[ RUN      ] Factorial_Instantiation/Factorial_Fixture.test_0/0
[       OK ] Factorial_Instantiation/Factorial_Fixture.test_0/0 (0 ms)
[ RUN      ] Factorial_Instantiation/Factorial_Fixture.test_0/1
[       OK ] Factorial_Instantiation/Factorial_Fixture.test_0/1 (0 ms)
[ RUN      ] Factorial_Instantiation/Factorial_Fixture.test_0/2
[       OK ] Factorial_Instantiation/Factorial_Fixture.test_0/2 (0 ms)
[ RUN      ] Factorial_Instantiation/Factorial_Fixture.test_0/3
[       OK ] Factorial_Instantiation/Factorial_Fixture.test_0/3 (0 ms)
[ RUN      ] Factorial_Instantiation/Factorial_Fixture.test_1/0
[       OK ] Factorial_Instantiation/Factorial_Fixture.test_1/0 (0 ms)
[ RUN      ] Factorial_Instantiation/Factorial_Fixture.test_1/1
[       OK ] Factorial_Instantiation/Factorial_Fixture.test_1/1 (0 ms)
[ RUN      ] Factorial_Instantiation/Factorial_Fixture.test_1/2
[       OK ] Factorial_Instantiation/Factorial_Fixture.test_1/2 (0 ms)
[ RUN      ] Factorial_Instantiation/Factorial_Fixture.test_1/3
[       OK ] Factorial_Instantiation/Factorial_Fixture.test_1/3 (0 ms)
[ RUN      ] Factorial_Instantiation/Factorial_Fixture.test_2/0
[       OK ] Factorial_Instantiation/Factorial_Fixture.test_2/0 (0 ms)
[ RUN      ] Factorial_Instantiation/Factorial_Fixture.test_2/1
[       OK ] Factorial_Instantiation/Factorial_Fixture.test_2/1 (0 ms)
[ RUN      ] Factorial_Instantiation/Factorial_Fixture.test_2/2
[       OK ] Factorial_Instantiation/Factorial_Fixture.test_2/2 (0 ms)
[ RUN      ] Factorial_Instantiation/Factorial_Fixture.test_2/3
[       OK ] Factorial_Instantiation/Factorial_Fixture.test_2/3 (0 ms)
[ RUN      ] Factorial_Instantiation/Factorial_Fixture.test_3/0
[       OK ] Factorial_Instantiation/Factorial_Fixture.test_3/0 (0 ms)
[ RUN      ] Factorial_Instantiation/Factorial_Fixture.test_3/1
[       OK ] Factorial_Instantiation/Factorial_Fixture.test_3/1 (0 ms)
[ RUN      ] Factorial_Instantiation/Factorial_Fixture.test_3/2
[       OK ] Factorial_Instantiation/Factorial_Fixture.test_3/2 (0 ms)
[ RUN      ] Factorial_Instantiation/Factorial_Fixture.test_3/3
[       OK ] Factorial_Instantiation/Factorial_Fixture.test_3/3 (0 ms)
[ RUN      ] Factorial_Instantiation/Factorial_Fixture.test_4/0
[       OK ] Factorial_Instantiation/Factorial_Fixture.test_4/0 (0 ms)
[ RUN      ] Factorial_Instantiation/Factorial_Fixture.test_4/1
[       OK ] Factorial_Instantiation/Factorial_Fixture.test_4/1 (0 ms)
[ RUN      ] Factorial_Instantiation/Factorial_Fixture.test_4/2
[       OK ] Factorial_Instantiation/Factorial_Fixture.test_4/2 (0 ms)
[ RUN      ] Factorial_Instantiation/Factorial_Fixture.test_4/3
[       OK ] Factorial_Instantiation/Factorial_Fixture.test_4/3 (0 ms)
[ RUN      ] Factorial_Instantiation/Factorial_Fixture.test_5/0
[       OK ] Factorial_Instantiation/Factorial_Fixture.test_5/0 (0 ms)
[ RUN      ] Factorial_Instantiation/Factorial_Fixture.test_5/1
[       OK ] Factorial_Instantiation/Factorial_Fixture.test_5/1 (0 ms)
[ RUN      ] Factorial_Instantiation/Factorial_Fixture.test_5/2
[       OK ] Factorial_Instantiation/Factorial_Fixture.test_5/2 (0 ms)
[ RUN      ] Factorial_Instantiation/Factorial_Fixture.test_5/3
[       OK ] Factorial_Instantiation/Factorial_Fixture.test_5/3 (0 ms)
[ RUN      ] Factorial_Instantiation/Factorial_Fixture.test_6/0
0.059 milliseconds

[       OK ] Factorial_Instantiation/Factorial_Fixture.test_6/0 (0 ms)
[ RUN      ] Factorial_Instantiation/Factorial_Fixture.test_6/1
0.062 milliseconds

[       OK ] Factorial_Instantiation/Factorial_Fixture.test_6/1 (0 ms)
[ RUN      ] Factorial_Instantiation/Factorial_Fixture.test_6/2
0.037 milliseconds

[       OK ] Factorial_Instantiation/Factorial_Fixture.test_6/2 (0 ms)
[ RUN      ] Factorial_Instantiation/Factorial_Fixture.test_6/3
0.409 milliseconds

[       OK ] Factorial_Instantiation/Factorial_Fixture.test_6/3 (1 ms)
[----------] 28 tests from Factorial_Instantiation/Factorial_Fixture (1 ms total)

[----------] Global test environment tear-down
[==========] 28 tests from 1 test case ran. (1 ms total)
[  PASSED  ] 28 tests.
*/
