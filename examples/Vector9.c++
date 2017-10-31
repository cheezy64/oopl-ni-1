// -----------
// Vector9.c++
// -----------

// http://en.cppreference.com/w/cpp/container/vector

#include <algorithm> // copy, equal, lexicographical_compare, max, swap
#include <cassert>   // assert
#include <memory>    // allocator
#include <stdexcept> // out_of_range
#include <utility>   // !=, <=, >, >=
#include <vector>    // vector

#include "gtest/gtest.h"

#include "Memory.h"  // my_destroy, my_uninitialized_copy, my_uninitialized_fill

using namespace std;
using namespace rel_ops;
using namespace testing;

template <typename T, typename A = allocator<T> >
class my_vector {
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

    public:
        friend bool operator == (const my_vector& lhs, const my_vector& rhs) {
            return (lhs.size() == rhs.size()) && equal(lhs.begin(), lhs.end(), rhs.begin());}

        friend bool operator < (const my_vector& lhs, const my_vector& rhs) {
            return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());}

        friend void swap (my_vector& x, my_vector& y) {
            x.swap(y);}

    private:
        allocator_type _a;

        pointer _b = nullptr;
        pointer _e = nullptr; // size
        pointer _l = nullptr; // capacity

    private:
        bool valid () const {
            return (!_b && !_e && !_l) || ((_b <= _e) && (_e <= _l));}

        my_vector (const my_vector& rhs, size_type c) :
                _a (rhs._a) {
            assert(c >= rhs.size());
            _b = _a.allocate(c);
            _e = _b + rhs.size();
            _l = _b + c;
            my_uninitialized_copy(_a, rhs._b, rhs._e, _b);
            assert(valid());}

    public:
        my_vector () :
                _a (),
                _b (nullptr),
                _e (nullptr),
                _l (nullptr) {
            assert(valid());}

        explicit my_vector (size_type s) :
                _a (),
                _b ((s == 0) ? nullptr : _a.allocate(s)),
                _e ((s == 0) ? nullptr : _b + s),
                _l ((s == 0) ? nullptr : _b + s) {
            my_uninitialized_fill(_a, _b, _e, value_type());
            assert(valid());}

        my_vector (size_type s, const_reference v) :
                _a (),
                _b ((s == 0) ? nullptr : _a.allocate(s)),
                _e ((s == 0) ? nullptr : _b + s),
                _l ((s == 0) ? nullptr : _b + s) {
            my_uninitialized_fill(_a, _b, _e, v);
            assert(valid());}

        my_vector (size_type s, const_reference v, const allocator_type& a) :
                _a (a),
                _b ((s == 0) ? nullptr : _a.allocate(s)),
                _e ((s == 0) ? nullptr : _b + s),
                _l ((s == 0) ? nullptr : _b + s) {
            my_uninitialized_fill(_a, _b, _e, v);
            assert(valid());}

        my_vector (const my_vector& rhs) :
                _a (rhs._a),
                _b ((rhs.size() == 0) ? nullptr : _a.allocate(rhs.size())),
                _e (_b + rhs.size()),
                _l (_e) {
            my_uninitialized_copy(_a, rhs._b, rhs._e, _b);
            assert(valid());}

        my_vector (my_vector&& rhs) {
            swap(rhs);}

        ~my_vector () {
            if (!empty()) {
                clear();
                _a.deallocate(_b, capacity());}
            assert(valid());}

        my_vector& operator = (const my_vector& rhs) {
            if (this == &rhs)
                return *this;
            if (rhs.size() == size())
                copy(rhs._b, rhs._e, _b);
            else if (rhs.size() < size()) {
                copy(rhs._b, rhs._e, _b);
                resize(rhs.size());}
            else if (rhs.size() <= capacity()) {
                copy(rhs._b, rhs._b + size(), _b);
                _e = my_uninitialized_copy(_a, rhs._b + size(), rhs._e, _e);}
            else {
                clear();
                reserve(rhs.size());
                _e = my_uninitialized_copy(_a, rhs._b, rhs._e, _b);}
            assert(valid());
            return *this;}

        my_vector& operator = (my_vector&& rhs) {
            if (this == &rhs)
                return *this;
            my_vector that(move(rhs));
            swap(that);
            return *this;}

        reference operator [] (size_type i) {
            return _b[i];}

        const_reference operator [] (size_type i) const {
            return const_cast<my_vector&>(*this)[i];}

        reference at (size_type i) throw (out_of_range) {
            if (i >= size())
                throw out_of_range("vector");
            return (*this)[i];}

        const_reference at (size_type i) const {
            return const_cast<my_vector&>(*this).at(i);}

        reference back () {
            assert(!empty());
            return *(_e - 1);}

        const_reference back () const {
            return const_cast<my_vector&>(*this).back();}

        iterator begin () {
            return _b;}

        const_iterator begin () const {
            return const_cast<my_vector&>(*this).begin();}

        size_type capacity () const {
            return (_b == nullptr) ? 0 : _l - _b;}

        void clear () {
            resize(0);
            assert(valid());}

        bool empty () const {
            return (size() == 0);}

        iterator end () {
            return _e;}

        const_iterator end () const {
            return const_cast<my_vector&>(*this).end();}

        reference front () {
            assert(!empty());
            return *_b;}

        const_reference front () const {
            return const_cast<my_vector&>(*this).front();}

        void pop_back () {
            assert(!empty());
            resize(size() - 1);
            assert(valid());}

        void push_back (const_reference v) {
            resize(size() + 1, v);
            assert(valid());}

        void reserve (size_type c) {
            if (c > capacity()) {
                my_vector x(*this, c);
                swap(x);}
            assert(valid());}

        void resize (size_type s, const_reference v = value_type()) {
            if (s == size())
                return;
            if (s < size())
                _e = my_destroy(_a, _b + s, _e);
            else if (s <= capacity()) {
                my_uninitialized_fill(_a, _e, _b + s, v);
                _e = _b + s;}
            else {
                #ifdef __APPLE__
                reserve(max(2 * capacity(), s));
                #else
                reserve(max(2 * size(), s));
                #endif
                resize(s, v);}
            assert(valid());}

        size_type size () const {
            return _b == nullptr ? 0 : _e - _b;}

        void swap (my_vector& rhs) {
            if (_a == rhs._a) {
                std::swap(_b, rhs._b);
                std::swap(_e, rhs._e);
                std::swap(_l, rhs._l);}
            else {
                my_vector x(*this);
                *this = rhs;
                rhs   = x;}
            assert(valid());}};

template <typename T>
struct Vector_Fixture : Test {
    using vector_type = T;
    using value_type  = typename vector_type::value_type;};

using
    vector_types =
    Types<
           vector<int>,
        my_vector<int>>;

TYPED_TEST_CASE(Vector_Fixture, vector_types);

TYPED_TEST(Vector_Fixture, test_1) {
    using vector_type = typename TestFixture::vector_type;

    const vector_type x;
    ASSERT_TRUE(x.empty());
    ASSERT_EQ(0, x.size());
    ASSERT_EQ(0, x.capacity());}

TYPED_TEST(Vector_Fixture, test_2) {
    using vector_type = typename TestFixture::vector_type;
    using value_type  = typename TestFixture::value_type;

    vector_type x(10);
    ASSERT_FALSE(x.empty());
    ASSERT_EQ(10, x.size());
    ASSERT_EQ(10, x.capacity());
    ASSERT_EQ(10, count(x.begin(), x.end(), value_type()));}

TYPED_TEST(Vector_Fixture, test_3) {
    using vector_type = typename TestFixture::vector_type;

    const vector_type x(10, 2);
    ASSERT_FALSE(x.empty());
    ASSERT_EQ(10, x.size());
    ASSERT_EQ(10, x.capacity());
    ASSERT_EQ(10, count(x.begin(), x.end(), 2));}

TYPED_TEST(Vector_Fixture, test_4) {
    using vector_type = typename TestFixture::vector_type;

    vector_type x(10);
    ASSERT_EQ(10, x.size());
    ASSERT_EQ(10, x.capacity());
    x.reserve(5);
    ASSERT_EQ(10, x.size());
    ASSERT_EQ(10, x.capacity());
    x.reserve(15);
    ASSERT_EQ(10, x.size());
    ASSERT_EQ(15, x.capacity());}

TYPED_TEST(Vector_Fixture, test_5) {
    using vector_type = typename TestFixture::vector_type;

    vector_type x(10);
    ASSERT_EQ(10, x.size());
    ASSERT_EQ(10, x.capacity());
    x.resize(5);
    ASSERT_EQ(5, x.size());
    ASSERT_EQ(10, x.capacity());
    x.resize(8);
    ASSERT_EQ(8, x.size());
    ASSERT_EQ(10, x.capacity());
    x.resize(15);
    ASSERT_EQ(15, x.size());
    #ifdef __APPLE__
    ASSERT_EQ(20, x.capacity());
    #else
    ASSERT_EQ(16, x.capacity());
    #endif
    x.resize(50);
    ASSERT_EQ(50, x.size());
    ASSERT_EQ(50, x.capacity());}

TYPED_TEST(Vector_Fixture, test_6) {
    using vector_type = typename TestFixture::vector_type;

    vector_type x(10);
    x[0] = 2;
    x[1] = 3;
    x[2] = 4;
    ASSERT_EQ(3, x[ 1]);
//  ASSERT_EQ(3, x[10]);
    try {
        ASSERT_EQ(3, x.at(10));
        ASSERT_TRUE(false);}
    catch (const out_of_range&)
        {}}

TYPED_TEST(Vector_Fixture, test_7) {
    using vector_type = typename TestFixture::vector_type;

    vector_type x;
    x.push_back(2);
    x.push_back(3);
    x.push_back(4);
    x.push_back(2);
    x.push_back(3);
    ASSERT_EQ(5, x.size());
    ASSERT_EQ(8, x.capacity());
    x.pop_back();
    ASSERT_EQ(4, x.size());
    ASSERT_EQ(8, x.capacity());}

TYPED_TEST(Vector_Fixture, test_8) {
    using vector_type = typename TestFixture::vector_type;

    vector_type x;
    x.push_back(2);
    x.push_back(3);
    x.push_back(4);
    ASSERT_EQ(3, x.size());
    ASSERT_EQ(4, x.capacity());
    const vector_type y(x);
    ASSERT_EQ(3, y.size());
    ASSERT_EQ(3, y.capacity());
    ASSERT_EQ(y, x);}

TYPED_TEST(Vector_Fixture, test_9) {
    using vector_type = typename TestFixture::vector_type;

    const vector_type x(10, 2);
    vector_type       y(20, 3);
    ASSERT_EQ(20, y.size());
    ASSERT_EQ(20, y.capacity());
    ASSERT_TRUE(x != y);
    y = x;
    ASSERT_EQ(10, y.size());
    ASSERT_EQ(20, y.capacity());
    ASSERT_EQ(y, x);}

TYPED_TEST(Vector_Fixture, test_10) {
    using vector_type = typename TestFixture::vector_type;

    const vector_type x(15, 2);
    vector_type       y(10, 3);
    ASSERT_EQ(10, y.size());
    ASSERT_EQ(10, y.capacity());
    y.push_back(3);
    ASSERT_EQ(11, y.size());
    ASSERT_EQ(20, y.capacity());
    ASSERT_TRUE(x != y);
    y = x;
    ASSERT_EQ(15, y.size());
    ASSERT_EQ(20, y.capacity());
    ASSERT_EQ(y, x);}

TYPED_TEST(Vector_Fixture, test_11) {
    using vector_type = typename TestFixture::vector_type;

    const vector_type x(20, 2);
    vector_type       y(10, 3);
    ASSERT_EQ(10, y.size());
    ASSERT_EQ(10, y.capacity());
    ASSERT_TRUE(x != y);
    y = x;
    ASSERT_EQ(20, y.size());
    ASSERT_EQ(20, y.capacity());
    ASSERT_EQ(y, x);}
