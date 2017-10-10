// ------------------
// RangeIterator2.c++
// ------------------

#include <algorithm> // equal
#include <iterator>  // input_iterator_tag, iterator

#include "gtest/gtest.h"

using namespace std;

template <typename T>
class RangeIterator : public iterator<input_iterator_tag, T> {
    friend bool operator == (const RangeIterator& lhs, const RangeIterator& rhs) {
        return (lhs._v == rhs._v);}

    friend bool operator != (const RangeIterator& lhs, const RangeIterator& rhs) {
        return !(lhs == rhs);}

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
    ASSERT_EQ(2, *b);
    RangeIterator<int>& x = ++b;
    ASSERT_EQ(&x, &b);
    ASSERT_EQ(b, e);}

TEST(RangeIteratorFixture, test_3) {
    RangeIterator<int> b = 2;
    RangeIterator<int> e = 4;
    ASSERT_NE(b, e);
    ASSERT_EQ(2, *b);
    ++b;
    ASSERT_NE(b, e);
    ASSERT_EQ(3, *b);
    RangeIterator<int> x = b++;
    ASSERT_NE(&x, &b);
    ASSERT_EQ(b, e);}

TEST(RangeIteratorFixture, test_4) {
    RangeIterator<int> b = 2;
    RangeIterator<int> e = 5;
    ASSERT_TRUE(equal(b, e, begin({2, 3, 4})));}
