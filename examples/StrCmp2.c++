// -----------
// StrCmp2.c++
// -----------

// http://en.cppreference.com/w/c/string/byte/strcmp

#include <cstring>    // strcmp
#include <functional> // function
#include <iostream>   // cout, endl
#include <string>     // strcmp

#include "gtest/gtest.h"

int my_strcmp (const char* a, const char* b) {
    while ((*a != 0) && (*a == *b)) {
        ++a;
        ++b;}
    return *a - *b;}

using namespace std;
using namespace testing;

using Str_Cmp_Signature = std::function<int (const char*, const char*)>;

struct Str_Cmp_Fixture : TestWithParam<Str_Cmp_Signature> {};

INSTANTIATE_TEST_CASE_P(
    Str_Cmp_Instantiation,
    Str_Cmp_Fixture,
    Values(
           strcmp,
        my_strcmp));

TEST_P(Str_Cmp_Fixture, test_1) {
	ASSERT_EQ(0, GetParam()("", ""));}

TEST_P(Str_Cmp_Fixture, test_2) {
	ASSERT_EQ(0, GetParam()("abc", "abc"));}

TEST_P(Str_Cmp_Fixture, test_3) {
	ASSERT_EQ('c' - 'b', GetParam()("abc", "abb"));}

TEST_P(Str_Cmp_Fixture, test_4) {
	ASSERT_EQ('c' - 0, GetParam()("abc", "ab"));}

TEST_P(Str_Cmp_Fixture, test_5) {
	ASSERT_EQ(0 - 'c', GetParam()("ab", "abc"));}
