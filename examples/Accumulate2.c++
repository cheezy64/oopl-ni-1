// ---------------
// Accumulate2.c++
// ---------------

// http://www.cplusplus.com/reference/algorithm/accumulate/

#include <functional> // function, multiplies, plus
#include <iostream>   // cout, endl
#include <numeric>    // accumulate
#include <list>       // list

#include "gtest/gtest.h"

using namespace std;
using namespace testing;

template <typename II, typename T, typename BF>
T my_accumulate (II b, II e, T v, BF f) {
    while (b != e) {
        v = f(v, *b);
        ++b;}
    return v;}

using Accumulate_List_Signature = function<int (list<int>::const_iterator, list<int>::const_iterator, int, function<int (int, int)>)>;

struct Accumulate_List_Fixture : TestWithParam<Accumulate_List_Signature>
    {};

INSTANTIATE_TEST_CASE_P(
    Accumulate_List_Instantiation,
    Accumulate_List_Fixture,
    Values(
           accumulate<list<int>::const_iterator, int, function<int (int, int)>>,
        my_accumulate<list<int>::const_iterator, int, function<int (int, int)>>));

TEST_P(Accumulate_List_Fixture, test_1) {
    const list<int> x = {2, 3, 4};
    ASSERT_EQ(9, GetParam()(x.begin(), x.end(), 0, plus<int>()));}

TEST_P(Accumulate_List_Fixture, test_2) {
    const list<int> x = {2, 3, 4};
    ASSERT_EQ(24, GetParam()(x.begin(), x.end(), 1, multiplies<int>()));}
