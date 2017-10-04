// ---------
// Iota2.c++
// ---------

// http://en.cppreference.com/w/cpp/algorithm/iota

#include <algorithm>  // equal
#include <functional> // function
#include <list>       // list
#include <numeric>    // iota

#include "gtest/gtest.h"

using namespace std;
using namespace testing;

template <typename FI, typename T>
void my_iota (FI b, FI e, T v) {
    while (b != e) {
        *b = v;
        ++b;
        ++v;}}

using IotaListSignature = function<void (list<int>::iterator, list<int>::iterator, int)>;

struct IotaListFixture : TestWithParam<IotaListSignature>
    {};

INSTANTIATE_TEST_CASE_P(
    IotaListInstantiation,
    IotaListFixture,
    Values(
           iota<list<int>::iterator, int>,
        my_iota<list<int>::iterator, int>));

TEST_P(IotaListFixture, test) {
    list<int>           x(5);
    list<int>::iterator b = begin(x);
    list<int>::iterator e = end(x);
    ++b;
    --e;
    GetParam()(b, e, 2);
    ASSERT_TRUE(equal(begin(x), end(x), begin({0, 2, 3, 4, 0})));}
