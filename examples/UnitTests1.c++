// --------------
// UnitTests1.c++
// --------------

// https://github.com/google/googletest
// https://github.com/google/googletest/blob/master/googletest/docs/Primer.md
// https://github.com/google/googletest/blob/master/googletest/docs/AdvancedGuide.md

#include <cassert>  // assert
#include <iostream> // cout, endl

#include "gtest/gtest.h"

int cycle_length (int n) {
    assert(n > 0);
    int c = 0;
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
    ASSERT_EQ(6, cycle_length( 5));}

TEST(UnitTestsFixture, test_3) {
    ASSERT_EQ(7, cycle_length(10));}

/*
% locate libgtest.a
/lusr/lib/libgtest.a



% locate libgtest_main.a
/lusr/lib/libgtest_main.a



% locate libpthread.a
/usr/lib/x86_64-linux-gnu/libpthread.a



% g++ -pedantic -std=c++14 -Wall UnitTests1.c++ -o UnitTests1 -lgtest -lgtest_main -pthread



% ./UnitTests1
Running main() from gtest_main.cc
[==========] Running 3 tests from 1 test case.
[----------] Global test environment set-up.
[----------] 3 tests from UnitTestsFixture
[ RUN      ] UnitTestsFixture.test_1
UnitTests1: UnitTests1.c++:23: int cycle_length(int): Assertion `c > 0' failed.
*/
