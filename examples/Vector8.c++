// -----------
// Vector8.c++
// -----------

// http://en.cppreference.com/w/cpp/container/vector

#include <algorithm>        // copy, equal, fill, lexicographical_compare, swap
#include <cstddef>          // ptrdiff_t, size_t
#include <initializer_list> // initializer_list
#include <memory>           // allocator
#include <utility>          // !=, <=, >, >=, move
#include <vector>           // vector

#include "gtest/gtest.h"

#include "Memory.h"  // my_destroy, my_uninitialized_copy, my_uninitialized_fill

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

template <typename T, typename A = allocator<T>>
class my_vector {
    friend bool operator == (const my_vector& lhs, const my_vector& rhs) {
        return (lhs.size() == rhs.size()) && equal(lhs.begin(), lhs.end(), rhs.begin());}

    friend bool operator < (const my_vector& lhs, const my_vector& rhs) {
        return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());}

    public:
        using allocator_type  = A;
        using value_type      = typename allocator_type::value_type;

        using size_type       = typename allocator_type::size_type;
        using difference_type = typename allocator_type::difference_type;

        using       pointer   = typename allocator_type::pointer;
        using const_pointer   = typename allocator_type::const_pointer;

        using       reference = typename allocator_type::reference;
        using const_reference = typename allocator_type::const_reference;

        using       iterator  = typename allocator_type::pointer;
        using const_iterator  = typename allocator_type::const_pointer;

    private:
        allocator_type _a;
        pointer        _b = nullptr;
        pointer        _e = nullptr;

    public:
        my_vector () = default;

        explicit my_vector (size_type s) :
                _a (),
                _b ((s == 0) ? nullptr : _a.allocate(s)),
                _e (_b + s) {
            my_uninitialized_fill(_a, _b, _e, value_type());}

        my_vector (size_type s, const_reference v) :
                _a (),
                _b ((s == 0) ? nullptr : _a.allocate(s)),
                _e (_b + s) {
            my_uninitialized_fill(_a, _b, _e, v);}

        my_vector (size_type s, const_reference v, const allocator_type& a) :
                _a (a),
                _b ((s == 0) ? nullptr : _a.allocate(s)),
                _e (_b + s) {
            my_uninitialized_fill(_a, _b, _e, v);}

        my_vector (initializer_list<value_type> rhs) :
                _a (),
                _b ((rhs.size() == 0) ? nullptr : _a.allocate(rhs.size())),
                _e (_b + rhs.size()) {
            my_uninitialized_copy(_a, rhs.begin(), rhs.end(), _b);}

        my_vector (initializer_list<value_type> rhs, const allocator_type& a) :
                _a (a),
                _b ((rhs.size() == 0) ? nullptr : _a.allocate(rhs.size())),
                _e (_b + rhs.size()) {
            my_uninitialized_copy(_a, rhs.begin(), rhs.end(), _b);}

        my_vector (const my_vector& rhs) :
                _a (rhs._a),
                _b ((rhs.size() == 0) ? nullptr : _a.allocate(rhs.size())),
                _e (_b + rhs.size()) {
            my_uninitialized_copy(_a, rhs._b, rhs._e, _b);}

        my_vector (my_vector&& rhs) {
            swap(rhs);}

        my_vector& operator = (const my_vector& rhs) {
            if (this == &rhs)
                return *this;
            my_vector that(rhs);
            swap(that);
            return *this;}

        my_vector& operator = (my_vector&& rhs) {
            if (this == &rhs)
                return *this;
            my_vector that(move(rhs));
            swap(that);
            return *this;}

        ~my_vector () {
            my_destroy(_a, _b, _e);
            _a.deallocate(_b, size());}

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
            return _e - _b;}

        void swap (my_vector& rhs) {
            if (_a == rhs._a) {
                std::swap(_b, rhs._b);
                std::swap(_e, rhs._e);}
            else {
                my_vector x(*this);
                *this = rhs;
                rhs   = x;}}};

template <typename T>
struct VectorFixture : Test {
    using vector_type    = T;
    using allocator_type = typename vector_type::allocator_type;};

using
    vector_types =
    Types<
           vector<int>,
        my_vector<int>,
           vector<int, allocator<int>>,
        my_vector<int, allocator<int>>>;

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

TYPED_TEST(VectorFixture, test_10) {
    using vector_type    = typename TestFixture::vector_type;
    using allocator_type = typename TestFixture::allocator_type;

    const vector_type x(3, 2, allocator_type());
    ASSERT_TRUE(equal(begin(x), end(x), begin({2, 2, 2})));}
