// -----------
// Shapes3.c++
// -----------

#include <cassert>  // assert
#include <iostream> // cout, endl, istream, ostream
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

void test () {
    {
    Shape x(2, 3);
    x.move(4, 5);
    assert(x.area() == 0);
//  x.radius();            // doesn't compile
    }

    {
    const Shape x(2, 3);
          Shape y(4, 5);
    assert(x != y);
    y = x;
    assert(x == y);
    }

    {
    Circle x(2, 3, 4);
    x.move(5, 6);
    assert(x.area()   == 3.14 * 4 * 4);
    assert(x.radius() == 4);
    }

    {
    const Circle x(2, 3, 4);
          Circle y(2, 3, 5);
    assert(x != y);
    y = x;
    assert(x == y);
    }

    {
//  Circle* const p = new Shape(2, 3);              // doesn't compile
    Shape*  const p = new Circle(2, 3, 4);
    p->move(5, 6);
    assert(p->area() == 3.14 * 4 * 4);
//  p->radius();                                    // doesn't compile
    if (Circle* const q = dynamic_cast<Circle*>(p))
        assert(q->radius() == 4);
    try {
        Circle& r = dynamic_cast<Circle&>(*p);
        assert(r.radius() == 4);}
    catch (const bad_cast& e) {
        assert(false);}
    delete p;
    }

    {
    const Shape* const p = new Circle(2, 3, 4);
          Shape* const q = new Circle(2, 3, 5);
    assert(*p != *q);
//  *q = *p;                                                    // illdefined
    if (const Circle* const r = dynamic_cast<const Circle*>(p))
        if (Circle* const s = dynamic_cast<Circle*>(q)) {
            assert(*r != *s);
            *s = *r;
            assert(*r == *s);}
    delete p;
    delete q;
    }

    {
//  const Circle a[] = {Shape(2, 3), Circle(4, 5, 6)}; // doesn't compile
    const Shape  a[] = {Shape(2, 3), Circle(4, 5, 6)};
    assert(a[0].area() == 0);
    assert(a[1].area() == 0);
    }

    {
    const Circle a[] = {Circle(2, 3, 4), Circle(5, 6, 7)};
    assert(a[0].area() == 3.14 * 4 * 4);
    assert(a[1].area() == 3.14 * 7 * 7);
    const Shape* const p = a;
    assert(p[0].area() == 3.14 * 4 * 4);
//  p[1].area();                                           // illdefined
    }}

int main () {
    cout << "Shapes3.c++" << endl;
    test();
    cout << "Done." << endl;
    return 0;}
