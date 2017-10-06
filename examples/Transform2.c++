// --------------
// Transform2.c++
// --------------

// http://www.cplusplus.com/reference/algorithm/transform/

#include <algorithm>  // transform, equal
#include <cmath>      // pow
#include <functional> // function
#include <list>       // list
#include <vector>     // vector

#include "gtest/gtest.h"

using namespace std;
using namespace testing;

template <typename II, typename OI, typename UF>
OI my_transform (II b, II e, OI x, UF f) {
    while (b != e) {
        *x = f(*b);
        ++b;
        ++x;}
    return x;}

using Transform_List_Signature = function<vector<int>::iterator (list<int>::const_iterator, list<int>::const_iterator, vector<int>::iterator, function<int (int)>)>;

struct Transform_List_Fixture : TestWithParam<Transform_List_Signature>
    {};

INSTANTIATE_TEST_CASE_P(
    Transform_List_Instantiation,
    Transform_List_Fixture,
    Values(
           transform<list<int>::const_iterator, vector<int>::iterator, function<int (int)>>,
        my_transform<list<int>::const_iterator, vector<int>::iterator, function<int (int)>>));

TEST_P(Transform_List_Fixture, test_1) {
    const list<int>       x = {2,  3,  4};
    vector<int>           y(5);
    function<int (int)>   f = [] (int n) -> int {return pow(n, 2);};
    vector<int>::iterator q = GetParam()(x.begin(), x.end(), begin(y) + 1, f);
    ASSERT_EQ(q, begin(y) + 4);
    ASSERT_TRUE(equal(begin(y), end(y), begin({0, 4, 9, 16, 0})));}

TEST_P(Transform_List_Fixture, test_2) {
    const list<int>       x = {2,  3,  4};
    vector<int>           y = {0,  0,  0,  0,   0};
    const list<int>       z = {0,  4,  9,  16,  0};
    const int             p = 2;
    function<int (int)>   f = [p] (int n) -> int {return pow(n, p);};
    vector<int>::iterator q = GetParam()(x.begin(), x.end(), begin(y) + 1, f);
    ASSERT_EQ(q, begin(y) + 4);
    ASSERT_TRUE(equal(begin(y), end(y), begin({0, 4, 9, 16, 0})));}
