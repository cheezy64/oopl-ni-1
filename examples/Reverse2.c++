// ------------
// Reverse2.c++
// ------------

// http://en.cppreference.com/w/cpp/algorithm/reverse

#include <algorithm>  // equal, reverse
#include <functional> // function
#include <list>       // list
#include <vector>     // vector

#include "gtest/gtest.h"

using namespace std;
using namespace testing;

template <typename BI>
void my_reverse_aux (BI b, BI e, std::bidirectional_iterator_tag) {
    while ((b != e) && (b != --e)) {
        std::swap(*b, *e);
        ++b;}}

template <typename RI>
void my_reverse_aux (RI b, RI e, std::random_access_iterator_tag) {
    while (b < --e) {
        std::swap(*b, *e);
        ++b;}}

template <typename I>
void my_reverse (I b, I e) {
    my_reverse_aux(b, e, typename std::iterator_traits<I>::iterator_category());}

using Reverse_List_Signature = function<void (list<int>::iterator, list<int>::iterator)>;

struct Reverse_List_Fixture : TestWithParam<Reverse_List_Signature>
    {};

INSTANTIATE_TEST_CASE_P(
    Reverse_List_Instantiation,
    Reverse_List_Fixture,
    Values(
           reverse<list<int>::iterator>,
        my_reverse<list<int>::iterator>));

TEST_P(Reverse_List_Fixture, test_1) {
    {
    list<int> x = {2, 3, 4};
    GetParam()(begin(x), end(x));
    assert(equal(begin(x), end(x), begin({4, 3, 2})));
    }}

TEST_P(Reverse_List_Fixture, test_2) {
    {
    list<int> x = {2, 3, 4, 5};
    GetParam()(begin(x), end(x));
    assert(equal(begin(x), end(x), begin({5, 4, 3, 2})));
    }}
