// -----------
// Vector2.c++
// -----------

// http://en.cppreference.com/w/cpp/container/vector

#include <algorithm>        // copy, equal, fill
#include <cstddef>          // ptrdiff_t, size_t
#include <initializer_list> // initializer_list
#include <vector>           // vector

#include "gtest/gtest.h"

using namespace std;
using namespace testing;

template <typename T>
class my_vector {
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
            fill(begin(), end(), value_type());}

        my_vector (size_type s, const_reference v) :
                _b ((s == 0) ? nullptr : new value_type[s]),
                _e (_b + s) {
            fill(begin(), end(), v);}

        my_vector (initializer_list<value_type> rhs) :
                _b ((rhs.size() == 0) ? nullptr : new value_type[rhs.size()]),
                _e (_b + rhs.size()) {
            copy(rhs.begin(), rhs.end(), begin());}

        my_vector             (const my_vector&)  = delete;
        my_vector& operator = (const my_vector&)  = delete;

        ~my_vector () {
            delete [] _b;}

        reference operator [] (size_type i) {
            return begin()[i];}

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
            return end() - begin();}};

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
