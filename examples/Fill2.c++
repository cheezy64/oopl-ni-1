// ---------
// Fill2.c++
// ---------

// http://en.cppreference.com/w/cpp/algorithm/fill

#include <algorithm>  // equal, fill
#include <functional> // function
#include <list>       // list

#include "gtest/gtest.h"

using namespace std;
using namespace testing;

template <typename FI, typename T>
void my_fill (FI b, FI e, const T& v) {
    while (b != e) {
        *b = v;
        ++b;}}

using FillListSignature = function<void (list<int>::iterator, list<int>::iterator, int)>;

struct FillListFixture : TestWithParam<FillListSignature>
    {};

INSTANTIATE_TEST_CASE_P(
    FillListInstantiation,
    FillListFixture,
    Values(
           fill<list<int>::iterator, int>,
        my_fill<list<int>::iterator, int>));

TEST_P(FillListFixture, test) {
    list<int>           x(5);
    list<int>::iterator b = begin(x);
    list<int>::iterator e = end(x);
    ++b;
    --e;
    GetParam()(b, e, 2);
    ASSERT_TRUE(equal(begin(x), end(x), begin({0, 2, 2, 2, 0})));}
