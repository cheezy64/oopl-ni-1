// -----------
// Shapes4.c++
// -----------

#include <iostream> // istream, ostream
#include <utility>  // !=

#include "gtest/gtest.h"

using namespace std;
using rel_ops::operator!=;

class Shape {
    friend bool operator == (const Shape& lhs, const Shape& rhs) {
        return lhs.equals(rhs);}

    friend std::istream& operator >> (std::istream& lhs, Shape& rhs) {
        return rhs.read(lhs);}

    friend std::ostream& operator << (std::ostream& lhs, const Shape& rhs) {
        return rhs.write(lhs);}

    private:
        int _x;
        int _y;

    protected:
        virtual bool equals (const Shape& rhs) const {
            return (_x == rhs._x) && (_y == rhs._y);}

        virtual std::istream& read (std::istream& in) {
            return in >> _x >> _y;}

        virtual std::ostream& write (std::ostream& out) const {
            return out << _x << " " << _y;}

    public:
        Shape (int x, int y) :
                _x (x),
                _y (y)
            {}

        Shape             (const Shape&) = default;
        virtual ~Shape    ()             = default;
        Shape& operator = (const Shape&) = default;

        virtual double area () const {
            return 0;}

        void move (int x, int y) {
            _x = x;
            _y = y;}};

class Circle : public Shape {
    friend bool operator == (const Circle& lhs, const Circle& rhs) {
        return lhs.equals(rhs);}

    friend std::istream& operator >> (std::istream& lhs, Circle& rhs) {
        return rhs.read(lhs);}

    friend std::ostream& operator << (std::ostream& lhs, const Circle& rhs) {
        return rhs.write(lhs);}

    private:
        int _r;

    protected:
        bool equals (const Shape& rhs) const override {
            if (const Circle* const p = dynamic_cast<const Circle*>(&rhs))
                return Shape::equals(*p) && (_r == p->_r);
            return false;}

        std::istream& read (std::istream& in) override {
            return Shape::read(in) >> _r;}

        std::ostream& write (std::ostream& out) const override {
            return Shape::write(out) << " " << _r;}

    public:
        Circle (int x, int y, int r) :
                Shape (x, y),
                _r    (r)
            {}

        Circle             (const Circle&) = default;
        ~Circle            ()              = default;
        Circle& operator = (const Circle&) = default;

        double area () const override {
            return 3.14 * _r * _r;}

        int radius () const {
            return _r;}};

TEST(ShapeFixture, test_1) {
    Shape x(2, 3);
    x.move(4, 5);
    ASSERT_EQ(x.area(), 0);
//  x.radius();               // doesn't compile
    }

TEST(ShapeFixture, test_2) {
    const Shape x(2, 3);
          Shape y(4, 5);
    ASSERT_NE(x, y);
    y = x;
    ASSERT_EQ(x, y);}

TEST(ShapeFixture, test_3) {
    Circle x(2, 3, 4);
    x.move(5, 6);
    ASSERT_EQ(x.area(),   3.14 * 4 * 4);
    ASSERT_EQ(x.radius(), 4);}

TEST(ShapeFixture, test_4) {
    const Circle x(2, 3, 4);
          Circle y(2, 3, 5);
    ASSERT_NE(x, y);
    y = x;
    ASSERT_EQ(x, y);}

TEST(ShapeFixture, test_5) {
//  Circle* const p = new Shape(2, 3);              // doesn't compile
    Shape*  const p = new Circle(2, 3, 4);
    p->move(5, 6);
    ASSERT_EQ(p->area(), 3.14 * 4 * 4);
//  p->radius();                                    // doesn't compile
    if (Circle* const q = dynamic_cast<Circle*>(p))
        ASSERT_EQ(q->radius(), 4);
    try {
        Circle& r = dynamic_cast<Circle&>(*p);
        ASSERT_EQ(r.radius(), 4);}
    catch (const bad_cast& e) {
        ASSERT_TRUE(false);}
    delete p;}

TEST(ShapeFixture, test_6) {
    const Shape* const p = new Circle(2, 3, 4);
          Shape* const q = new Circle(2, 3, 5);
    ASSERT_NE(*p, *q);
//  *q = *p;                                                    // illdefined
    if (const Circle* const r = dynamic_cast<const Circle*>(p))
        if (Circle* const s = dynamic_cast<Circle*>(q)) {
            ASSERT_NE(*r, *s);
            *s = *r;
            ASSERT_EQ(*r, *s);}
    delete p;
    delete q;}

TEST(ShapeFixture, test_7) {
//  const Circle a[] = {Shape(2, 3), Circle(4, 5, 6)}; // doesn't compile
    const Shape  a[] = {Shape(2, 3), Circle(4, 5, 6)};
    ASSERT_EQ(a[0].area(), 0);
    ASSERT_EQ(a[1].area(), 0);}

TEST(ShapeFixture, test_8) {
    const Circle a[] = {Circle(2, 3, 4), Circle(5, 6, 7)};
    ASSERT_EQ(a[0].area(), 3.14 * 4 * 4);
    ASSERT_EQ(a[1].area(), 3.14 * 7 * 7);
    const Shape* const p = a;
    ASSERT_EQ(p[0].area(), 3.14 * 4 * 4);
//  p[1].area();                                           // illdefined
    }
