#ifndef PENTAGONE_HPP
#define PENTAGONE_HPP

#include "point.hpp"
#include "figure.hpp"
#include <exception>

template <Numeric T>
class Pentagone final: public Figure<T> {

   protected:
    Point<T> left_lower;
    Point<T> right_lower;
    Point<T> left_middle;
    Point<T> right_middle;
    Point<T> upper;

    static void check(const Point<T>& left_lower, const Point<T>& right_lower, const Point<T>& left_upper, const Point<T>& right_upper, const Point<T>& upper) {
        T d12 = Point<T>::distance(left_lower, right_lower);
        T d23 = Point<T>::distance(right_lower, right_upper);
        T d34 = Point<T>::distance(right_upper, left_upper);
        T d45 = Point<T>::distance(left_upper, upper);
        T d51 = Point<T>::distance(upper, left_lower);

        if (std::abs(d12) < Point<T>::eps || std::abs(d23) < Point<T>::eps || std::abs(d34) < Point<T>::eps || std::abs(d45) < Point<T>::eps || std::abs(d51) < Point<T>::eps) {
            throw std::logic_error("Points do not form a pentagone");
        }

    }
    virtual std::ostream& print(std::ostream& os) const noexcept override {
        os << "Name: " << this -> figure_name << "\n";
        os << "Left Lower: " << this -> left_lower << "\n";
        os << "Right Lower: " << this -> right_lower << "\n";
        os << "Left Middle: " << this -> left_middle << "\n";
        os << "Right Middle: " << this -> right_middle << "\n";
        os << "Upper: " << this -> upper << "\n";
        return os;
    }
    virtual std::istream& input(std::istream& is) noexcept override {
        std::cout << "Enter figure name: ";
        is >> this -> figure_name;
        std::cout << "Enter left_lower point: ";
        is >> this -> left_lower;
        std::cout << "Enter right_lower point: ";
        is >> this -> right_lower;
        std::cout << "Enter left_middle point: ";
        is >> this -> left_middle;
        std::cout << "Enter right_middle point: ";
        is >> this -> right_middle;
        std::cout << "Enter upper point: ";
        is >> this -> upper;
        return is;
    }

  public:
    Pentagone() = default;
    Pentagone(const Point<T>& _left_lower, const Point<T>& _right_lower, const Point<T>&  _left_middle, const Point<T>& _right_middle, const Point<T>& _upper, const std::string& _figure_name):
    left_lower(Point<T>{}), left_middle(Point<T>{}), right_lower(Point<T>{}), right_middle(Point<T>{}), upper(Point<T>{}), Figure<T>(_figure_name)
    {
        check(_left_lower, _right_lower, _left_middle, _right_middle, _upper);

        left_lower = _left_lower;
        left_middle = _left_middle;
        right_lower = _right_lower;
        right_middle = _right_middle;
        upper = _upper;
    }

    virtual T area() const noexcept override {
        return std::abs((left_lower.x*right_lower.y + right_lower.x*right_middle.y +right_middle.x*upper.y + upper.x*left_middle.y + left_middle.x*left_lower.y)
    -
    (left_lower.y*right_lower.x + right_lower.y*right_middle.x +right_middle.y*upper.x + upper.y*left_middle.x + left_middle.y*left_lower.x));
    }
    virtual T perimetr() const noexcept override {
        double a = Point<T>::distance(left_middle, left_lower);
        double b = Point<T>::distance(right_middle, right_lower);
        double c = Point<T>::distance(right_lower, left_lower);
        double d = Point<T>::distance(upper, right_middle);
        double e = Point<T>::distance(upper, left_middle);

        return a + b + c + d + e;
    }
    virtual Point<T> center() const noexcept override {
        T xCenter =  (left_lower.x + left_middle.x + right_lower.x + right_middle.x + upper.x)*0.2;
        T yCenter =  (left_lower.y + left_middle.y + right_lower.y + right_middle.y + upper.y)*0.2;

        return Point<T>(xCenter, yCenter);
    }

    explicit virtual operator T() const noexcept override {
        return this -> area();
    }
    virtual bool operator==(const Figure<T>& other) const noexcept override {
        const Pentagone<T>* p = dynamic_cast<const Pentagone<T>*>(&other);
        if (p == nullptr) {
            return false;
        }
        return left_lower == p -> left_lower && 
        left_middle == p -> left_middle && 
        right_lower == p -> right_lower && 
        right_middle == p -> right_middle && 
        upper == p -> upper;
    }
    virtual bool operator!=(const Figure<T>& other) const noexcept override {
        return !(*this == other);
    }

    friend std::ostream& operator<<(std::ostream& os, const Pentagone<T>& p) noexcept {
        return p.print(os);
    }
    friend std::istream& operator>>(std::istream& is, Pentagone<T>& p) {
        p.input(is);
        //Pentagone::check(p.left_lower, p.right_lower, p.left_middle, p.right_middle, p.upper);
        return is;
    }
};
#endif
