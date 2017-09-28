// ----------
// Equal2.c++
// ----------

// http://en.cppreference.com/w/cpp/algorithm/equal

#include <algorithm>  // equal
#include <functional> // function
#include <list>       // list
#include <vector>     // vector

#include "gtest/gtest.h"

using namespace std;
using namespace testing;

template <typename II1, typename II2>
bool my_equal (II1 b, II1 e, II2 c) {
    while (b != e) {
        if (*b != *c)
            return false;
        ++b;
        ++c;}
    return true;}

using EqualListSignature = function<bool (list<int>::const_iterator, list<int>::const_iterator, vector<int>::const_iterator)>;

struct EqualListFixture : TestWithParam<EqualListSignature>
    {};

INSTANTIATE_TEST_CASE_P(
    EqualListInstantiation,
    EqualListFixture,
    Values(
        my_equal<list<int>::const_iterator, vector<int>::const_iterator>,
        my_equal<list<int>::const_iterator, vector<int>::const_iterator>));

TEST_P(EqualListFixture, test_1) {
    const list<int>   x = {2, 3, 4};
    const vector<int> y = {0, 2, 3, 4, 0};
    ASSERT_FALSE(GetParam()(begin(x), end(x), begin(y)));}

TEST_P(EqualListFixture, test_2) {
    const list<int>   x = {2, 3, 4};
    const vector<int> y = {0, 2, 3, 4, 0};
    ASSERT_TRUE(GetParam()(begin(x), end(x), begin(y) + 1));}
