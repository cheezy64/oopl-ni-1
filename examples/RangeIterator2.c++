// ------------------
// RangeIterator2.c++
// ------------------

#include <algorithm> // equal
#include <iterator>  // input_iterator_tag, iterator
#include <utility>   // !=

#include "gtest/gtest.h"

using namespace std;
using std::rel_ops::operator!=;

template <typename T>
class RangeIterator : public iterator<input_iterator_tag, T> {
    friend bool operator == (const RangeIterator& lhs, const RangeIterator& rhs) {
        return (lhs._v == rhs._v);}

    private:
        T _v;

    public:
        RangeIterator (const T& v) :
                _v (v)
            {}

        T operator * () const {
            return _v;}

        RangeIterator& operator ++ () {
            ++_v;
            return *this;}

        RangeIterator operator ++ (int) {
            RangeIterator x = *this;
            ++*this;
            return x;}};

TEST(RangeIteratorFixture, test_1) {
    const RangeIterator<int> b = 2;
    const RangeIterator<int> e = 2;
    ASSERT_EQ(b, e);}

TEST(RangeIteratorFixture, test_2) {
    RangeIterator<int> b = 2;
    RangeIterator<int> e = 3;
    ASSERT_NE(b, e);
    ASSERT_EQ(*b, 2);
    RangeIterator<int>& x = ++b;
    ASSERT_EQ(&x, &b);
    ASSERT_EQ(b, e);}

TEST(RangeIteratorFixture, test_3) {
    RangeIterator<int> b = 2;
    RangeIterator<int> e = 4;
    ASSERT_NE(b, e);
    ASSERT_EQ(*b, 2);
    ++b;
    ASSERT_NE(b, e);
    ASSERT_EQ(*b, 3);
    RangeIterator<int> x = b++;
    ASSERT_NE(&x, &b);
    ASSERT_EQ(b, e);}

TEST(RangeIteratorFixture, test_4) {
    RangeIterator<int> b = 2;
    RangeIterator<int> e = 5;
    ASSERT_TRUE(equal(b, e, begin({2, 3, 4})));}
