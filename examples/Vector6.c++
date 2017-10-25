// -----------
// Vector6.c++
// -----------

// http://en.cppreference.com/w/cpp/container/vector

#include <algorithm>        // copy, equal, fill, lexicographical_compare, swap
#include <cstddef>          // ptrdiff_t, size_t
#include <initializer_list> // initializer_list
#include <utility>          // !=, <=, >, >=, move
#include <vector>           // vector

#include "gtest/gtest.h"

using namespace std;
using namespace testing;

/*
namespace std     {
namespace rel_ops {

template <typename T>
inline bool operator != (const T& lhs, const T& rhs) {
    return !(lhs == rhs);}

template <typename T>
inline bool operator <= (const T& lhs, const T& rhs) {
    return !(rhs < lhs);}

template <typename T>
inline bool operator > (const T& lhs, const T& rhs) {
    return (rhs < lhs);}

template <typename T>
inline bool operator >= (const T& lhs, const T& rhs) {
    return !(lhs < rhs);}

} // rel_ops
} // std;
*/

using rel_ops::operator!=;
using rel_ops::operator<=;
using rel_ops::operator>;
using rel_ops::operator>=;

template <typename T>
class my_vector {
    friend bool operator == (const my_vector& lhs, const my_vector& rhs) {
        return (lhs.size() == rhs.size()) && equal(lhs.begin(), lhs.end(), rhs.begin());}

    friend bool operator < (const my_vector& lhs, const my_vector& rhs) {
        return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());}

    public:
        using value_type      = T;

        using size_type       = size_t;
        using difference_type = ptrdiff_t;

        using       pointer   =       value_type*;
        using const_pointer   = const value_type*;

        using       reference =       value_type&;
        using const_reference = const value_type&;

        using       iterator  =       pointer;
        using const_iterator  = const_pointer;

    private:
        pointer _b = nullptr;
        pointer _e = nullptr;

    public:
        my_vector () = default;

        explicit my_vector (size_type s) :
                _b ((s == 0) ? nullptr : new value_type[s]),
                _e (_b + s) {
            fill(_b, _e, value_type());}

        my_vector (size_type s, const_reference v) :
                _b ((s == 0) ? nullptr : new value_type[s]),
                _e (_b + s) {
            fill(_b, _e, v);}

        my_vector (initializer_list<value_type> rhs) :
                _b ((rhs.size() == 0) ? nullptr : new value_type[rhs.size()]),
                _e (_b + rhs.size()) {
            copy(rhs.begin(), rhs.end(), _b);}

        my_vector (const my_vector& rhs) :
                _b ((rhs.size() == 0) ? nullptr : new value_type[rhs.size()]),
                _e (_b + rhs.size()) {
            copy(rhs._b, rhs._e, _b);}

        my_vector (my_vector&& rhs) {
            swap(_b, rhs._b);
            swap(_e, rhs._e);}

        my_vector& operator = (const my_vector& rhs) {
            if (this == &rhs)
                return *this;
            my_vector that(rhs);
            swap(_b, that._b);
            swap(_e, that._e);
            return *this;}

        my_vector& operator = (my_vector&& rhs) {
            if (this == &rhs)
                return *this;
            my_vector that(move(rhs));
            swap(_b, that._b);
            swap(_e, that._e);
            return *this;}

        ~my_vector () {
            delete [] _b;}

        reference operator [] (size_type i) {
            return _b[i];}

        const_reference operator [] (size_type i) const {
            return (*const_cast<my_vector*>(this))[i];}

        iterator begin () {
            return _b;}

        const_iterator begin () const {
            return const_cast<my_vector*>(this)->begin();}

        iterator end () {
            return _e;}

        const_iterator end () const {
            return const_cast<my_vector*>(this)->end();}

        size_type size () const {
            return _e - _b;}};

template <typename T>
struct VectorFixture : Test {
    using vector_type = T;};

using
    vector_types =
    Types<
           vector<int>,
        my_vector<int>>;

TYPED_TEST_CASE(VectorFixture, vector_types);

TYPED_TEST(VectorFixture, test_1) {
    using vector_type = typename TestFixture::vector_type;

    vector_type x;
    ASSERT_EQ(0, x.size());}

TYPED_TEST(VectorFixture, test_2) {
    using vector_type = typename TestFixture::vector_type;

    vector_type x(3);
    ASSERT_EQ(3, x.size());
    ASSERT_TRUE(equal(begin(x), end(x), begin({0, 0, 0})));
    ASSERT_EQ(0, x[1]);
    x[1] = 2;
    ASSERT_TRUE(equal(begin(x), end(x), begin({0, 2, 0})));}

TYPED_TEST(VectorFixture, test_3) {
    using vector_type = typename TestFixture::vector_type;

    const vector_type x(3, 2);
    ASSERT_EQ(3, x.size());
    ASSERT_TRUE(equal(begin(x), end(x), begin({2, 2, 2})));
    ASSERT_EQ(2, x[1]);
    // x[1] = 3;                                            // error: cannot assign to return value because function 'operator[]' returns a const value
    const vector_type y(6, 2);
    ASSERT_TRUE(equal(begin(x), end(x), begin(y)));}

TYPED_TEST(VectorFixture, test_4) {
    using vector_type = typename TestFixture::vector_type;

    const vector_type x = {2, 3, 4};
    ASSERT_EQ(3, x.size());
    ASSERT_TRUE(equal(begin(x), end(x), begin({2, 3, 4})));}

TYPED_TEST(VectorFixture, test_5) {
    using vector_type = typename TestFixture::vector_type;

    const vector_type x(10, 2);
    const vector_type y = x;
    ASSERT_NE(begin(x), begin(y));
    ASSERT_EQ(x, y);}

TYPED_TEST(VectorFixture, test_6) {
    using vector_type = typename TestFixture::vector_type;

    const vector_type x(20, 3);
          vector_type y(10, 2);
    y = x;
    ASSERT_NE(begin(x), begin(y));
    ASSERT_EQ(x, y);}

TYPED_TEST(VectorFixture, test_7) {
    using vector_type = typename TestFixture::vector_type;

    const vector_type x(10, 2);
    const vector_type y(10, 2);
    const vector_type z(10, 3);
    ASSERT_EQ(x, y);
    ASSERT_NE(x, z);
    ASSERT_LT(x, z);
    ASSERT_LE(x, y);
    ASSERT_GT(z, x);
    ASSERT_GE(x, y);}

TYPED_TEST(VectorFixture, test_8) {
    using vector_type = typename TestFixture::vector_type;

                   vector_type           x(10, 2);
    typename       vector_type::iterator b = begin(x);
             const vector_type           y = move(x);
    ASSERT_EQ( 0, x.size());
    ASSERT_EQ(10, y.size());
    ASSERT_EQ(b,  begin(y));}

TYPED_TEST(VectorFixture, test_9) {
    using vector_type = typename TestFixture::vector_type;

             vector_type           x(20, 3);
             vector_type           y(10, 2);
    typename vector_type::iterator b = begin(x);
    y = move(x);
    ASSERT_EQ( 0, x.size());
    ASSERT_EQ(20, y.size());
    ASSERT_EQ(b,  begin(y));}
