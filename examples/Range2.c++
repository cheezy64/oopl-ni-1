// ----------
// Range2.c++
// ----------

#include <algorithm> // equal
#include <iterator>  // input_iterator_tag, iterator

#include "gtest/gtest.h"

using namespace std;

template <typename T>
class Range {
    private:
        T _b;
        T _e;

    public:
        class iterator : public std::iterator<input_iterator_tag, T> {
            friend bool operator == (const iterator& lhs, const iterator& rhs) {
                return (lhs._v == rhs._v);}

            friend bool operator != (const iterator& lhs, const iterator& rhs) {
                return !(lhs == rhs);}

            private:
                T _v;

            public:
                iterator (const T& v) :
                        _v (v)
                    {}

                T operator * () const {
                    return _v;}

                iterator& operator ++ () {
                    ++_v;
                    return *this;}

                iterator operator ++ (int) {
                    iterator x = *this;
                    ++*this;
                    return x;}};

        Range (const T& b, const T& e) :
                _b (b),
                _e (e)
            {}

        iterator begin () const {
            return _b;}

        iterator end () const {
            return _e;}};

TEST(RangeFixture, test_1) {
    const Range<int> x(2, 2);
    const Range<int>::iterator b = begin(x);
    const Range<int>::iterator e = end(x);
    ASSERT_EQ(b, e);}

TEST(RangeFixture, test_2) {
    Range<int> x(2, 3);
    Range<int>::iterator b = begin(x);
    Range<int>::iterator e = end(x);
    ASSERT_NE(b, e);
    ASSERT_EQ(2, *b);
    Range<int>::iterator& y = ++b;
    ASSERT_EQ(&y, &b);
    ASSERT_EQ(b, e);}

TEST(RangeFixture, test_3) {
    Range<int> x(2, 4);
    Range<int>::iterator b = begin(x);
    Range<int>::iterator e = end(x);
    ASSERT_NE(b, e);
    ASSERT_EQ(2, *b);
    ++b;
    ASSERT_NE(b, e);
    ASSERT_EQ(3, *b);
    b++;
    ASSERT_EQ(b, e);}

TEST(RangeFixture, test_4) {
    Range<int> x(2, 5);
    ASSERT_TRUE(equal(begin(x), end(x), begin({2, 3, 4})));}
