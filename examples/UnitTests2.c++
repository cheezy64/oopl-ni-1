// --------------
// UnitTests2.c++
// --------------

// https://github.com/google/googletest
// https://github.com/google/googletest/blob/master/googletest/docs/Primer.md
// https://github.com/google/googletest/blob/master/googletest/docs/AdvancedGuide.md

#include <cassert>  // assert
#include <iostream> // cout, endl

#include "gtest/gtest.h"

int cycle_length (int n) {
    assert(n > 0);
    int c = 1;
    while (n > 1) {
        if ((n % 2) == 0)
            n = (n / 2);
        else
            n = (3 * n) + 1;
        ++c;}
    assert(c > 0);
    return c;}

TEST(UnitTestsFixture, test_1) {
    ASSERT_EQ(1, cycle_length( 1));}

TEST(UnitTestsFixture, test_2) {
    ASSERT_EQ(5, cycle_length( 5));}

TEST(UnitTestsFixture, test_3) {
    ASSERT_EQ(7, cycle_length(10));}

/*
% ./UnitTests2
Running main() from gtest_main.cc
[==========] Running 3 tests from 1 test case.
[----------] Global test environment set-up.
[----------] 3 tests from UnitTestsFixture
[ RUN      ] UnitTestsFixture.test_1
[       OK ] UnitTestsFixture.test_1 (0 ms)
[ RUN      ] UnitTestsFixture.test_2
UnitTests2.c++:30: Failure
      Expected: 5
To be equal to: cycle_length( 5)
      Which is: 6
[  FAILED  ] UnitTestsFixture.test_2 (0 ms)
[ RUN      ] UnitTestsFixture.test_3
[       OK ] UnitTestsFixture.test_3 (0 ms)
[----------] 3 tests from UnitTestsFixture (0 ms total)

[----------] Global test environment tear-down
[==========] 3 tests from 1 test case ran. (0 ms total)
[  PASSED  ] 2 tests.
[  FAILED  ] 1 test, listed below:
[  FAILED  ] UnitTestsFixture.test_2

 1 FAILED TEST
*/
