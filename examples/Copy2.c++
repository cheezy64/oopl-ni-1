// ---------
// Copy2.c++
// ---------

// http://en.cppreference.com/w/cpp/algorithm/copy

#include <algorithm>  // copy, equal
#include <functional> // function
#include <list>       // list
#include <vector>     // vector

#include "gtest/gtest.h"

using namespace std;
using namespace testing;

template <typename II, typename OI>
OI my_copy (II b, II e, OI x) {
    while (b != e) {
        *x = *b;
        ++b;
        ++x;}
    return x;}

using CopyListSignature = function<vector<int>::iterator (list<int>::const_iterator, list<int>::const_iterator, vector<int>::iterator)>;

struct CopyListFixture : TestWithParam<CopyListSignature>
    {};

INSTANTIATE_TEST_CASE_P(
    CopyListInstantiation,
    CopyListFixture,
    Values(
           copy<list<int>::const_iterator, vector<int>::iterator>,
        my_copy<list<int>::const_iterator, vector<int>::iterator>));

TEST_P(CopyListFixture, test_1) {
    const list<int> x = {2, 3, 4};
    vector<int>     y(5);
    vector<int>::iterator p = GetParam()(begin(x), end(x), begin(y) + 1);
    ASSERT_EQ(p, begin(y) + 4);
    ASSERT_TRUE(equal(begin(y), end(y), begin({0, 2, 3, 4, 0})));}
