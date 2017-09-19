// ------------
// IsPrime2.c++
// ------------

// https://en.wikipedia.org/wiki/Primality_test

#include <cmath> // sqrt

#include "gtest/gtest.h"

bool is_prime (int n) {
    assert(n > 0);
    if (n == 2)
        return true;
    if ((n == 1) || ((n % 2) == 0))
        return false;
    for (int i = 3; i < (std::sqrt(n) + 1); i += 2)
        if ((n % i) == 0)
            return false;
    return true;}

TEST(IsPrimeFixture, test_1) {
    ASSERT_FALSE(is_prime( 1));}

TEST(IsPrimeFixture, test_2) {
    ASSERT_TRUE(is_prime( 2));}

TEST(IsPrimeFixture, test_3) {
    ASSERT_TRUE(is_prime( 3));}

TEST(IsPrimeFixture, test_4) {
    ASSERT_FALSE(is_prime( 4));}

TEST(IsPrimeFixture, test_5) {
    ASSERT_TRUE(is_prime( 5));}

TEST(IsPrimeFixture, test_7) {
    ASSERT_TRUE(is_prime( 7));}

TEST(IsPrimeFixture, test_9) {
    ASSERT_FALSE(is_prime( 9));}

TEST(IsPrimeFixture, test_27) {
    ASSERT_FALSE(is_prime(27));}

TEST(IsPrimeFixture, test_29) {
    ASSERT_TRUE(is_prime(29));}
