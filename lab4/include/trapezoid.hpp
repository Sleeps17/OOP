#ifndef TRAPEZOID_HPP
#define TRAPEZOID_HPP

#include "point.hpp"
#include "figure.hpp"
#include <exception>

template<Numeric T>
class Trapezoid final: public Figure<T> {

  protected:
    Point<T> left_lower;
    Point<T> right_lower;
    Point<T> left_upper;
    Point<T> right_upper;

    static void check(const Point<T>& _left_lower, const Point<T>& _right_lower, const Point<T>& _left_upper, const Point<T>& _right_upper) {
        T dy1 = std::abs(_left_upper.y - _right_upper.y);
        T dx1 = std::abs(_left_upper.x - _right_upper.x);

        T dy2 = std::abs(_left_lower.y - _right_lower.y);
        T dx2 = std::abs(_left_lower.x - _right_lower.x);

        if (dy1/dx1 - dy2/dx1 < Point<T>::eps) {
            return;
        }

        throw std::invalid_argument("Points do not from a trapezoid");
    }
    virtual std::ostream& print(std::ostream& os) const noexcept override {
        os << "Name: " << this -> figure_name << "\n";
        os << "Left Upper: " << this -> left_upper << "\n";
        os << "Right Upper: " << this -> right_upper << "\n";
        os << "Left Lower: " << this -> left_lower << "\n";
        os << "Right Lower: " << this -> right_lower << "\n";
        return os;
    }
    virtual std::istream& input(std::istream& is) noexcept override {
        std::cout << "Enter figure name: ";
        is >> this -> figure_name;
        std::cout << "Enter left_lower point: ";
        is >> this -> left_lower;
        std::cout << "Enter right_lower point: ";
        is >> this -> right_lower;
        std::cout << "Enter left_upper point: ";
        is >> this -> left_upper;
        std::cout << "Enter right_upper point: ";
        is >> this -> right_upper;
        return is;
    }

  public:
    Trapezoid() = default;
    Trapezoid(const Point<T>& _left_lower, const Point<T>& _right_lower, const Point<T>&  _left_upper, const Point<T>& _right_upper, const std::string& _figure_name):
    left_lower(Point<T>{}), right_lower(Point<T>{}), left_upper(Point<T>{}), right_upper(Point<T>{}), Figure<T>(_figure_name) 
    {
    
    check(_left_lower, _right_lower, _left_upper, _right_upper);

    left_lower = _left_lower;
    left_upper = _left_upper;
    right_lower = _right_lower;
    right_upper = _right_upper;
    }

    virtual T area() const noexcept override {
        T x = Point<T>::distance(left_upper, left_lower);
        T y = Point<T>::distance(right_upper, right_lower);
        T a = Point<T>::distance(left_upper, left_lower);
        T z = Point<T>::distance(left_lower, right_lower);

        T c = (x*x - y*y + z*z -2*a*z + a*a) / (2*(z - a));
        T h = std::sqrt(x*x - c*c);

        return (a + z)*0.5*h;
    }
    virtual T perimetr() const noexcept override {
        T a = Point<T>::distance(left_upper, left_lower);
        T b = Point<T>::distance(left_upper, right_upper);
        T c = Point<T>::distance(right_upper, right_lower);
        T d = Point<T>::distance(right_lower, left_lower);

        return a + b + c + d;
    }
    virtual Point<T> center() const noexcept override {
        T xCenter = (left_lower.x + left_upper.x + right_lower.x + right_upper.x)*0.25;
        T yCenter = (left_lower.y + left_upper.y + right_lower.y + right_upper.y)*0.25;

        return Point<T>(xCenter, yCenter);
    }

    explicit virtual operator T() const noexcept {
        return this -> area();
    }
    virtual bool operator==(const Figure<T>& other) const noexcept override {
        const Trapezoid<T>* t = dynamic_cast<const Trapezoid<T>*>(&other);
        if (t == nullptr) {
            return false;
        }
        return left_lower == t -> left_lower 
        && left_upper == t -> left_upper 
        && right_lower == t -> right_lower 
        && right_upper == t -> right_upper;
    }
    virtual bool operator!=(const Figure<T>& other) const noexcept override {
        return !(*this == other);
    }

    friend std::ostream& operator<<(std::ostream& os, const Trapezoid<T>& t) noexcept {
        return t.print(os);
    }
    friend std::istream& operator>>(std::istream& is, Trapezoid<T>& t) {
        t.input(is);
        Trapezoid<T>::check(t.left_lower, t.right_lower, t.left_upper, t.right_upper);
        return is;
    }
};

#endif