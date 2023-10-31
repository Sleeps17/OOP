#ifndef RHOMB_HPP
#define RHOMB_HPP

#include <exception>
#include "point.hpp"
#include "figure.hpp"

template <Numeric T>
class Rhomb final: public Figure<T> {
    
  protected:
    Point<T> upper;
    Point<T> lower;
    Point<T> left;
    Point<T> right;

    static void check(const Point<T>& _upper, const Point<T>& _lower, const Point<T>& _left, const Point<T>& _right) {
        T d1 = Point<T>::distance(_upper, _right);
        T d2 = Point<T>::distance(_upper, _left);
        T d3 = Point<T>::distance(_lower, _right);
        T d4 = Point<T>::distance(_lower, _left);
        
        if (d1 != d2 || d2 != d3 || d3 != d4) {
            throw std::invalid_argument("Points do not form a rhomb");
        }
    }
    virtual std::ostream& print(std::ostream& os) const noexcept override {
        os << "Name: " << this -> figure_name << "\n";
        os << "Upper: " << upper << "\n";
        os << "Lower: " << lower << "\n";
        os << "Left: " << left << "\n";
        os << "Right: " << right << "\n";
        return os;
    }
    virtual std::istream& input(std::istream& is) noexcept override {
        std::cout << "Enter figure name: ";
        is >> this -> figure_name;
        std::cout << "Enter upper point: ";
        is >> upper;
        std::cout << "Enter lower point: ";
        is >> lower;
        std::cout << "Enter left point: ";
        is >> left;
        std::cout << "Enter right point: ";
        is >> right;
        return is;
    }

  public:
    Rhomb() = default;
    Rhomb(const Point<T>& _upper, const Point<T>& _lower, const Point<T>& _left, const Point<T>& _right, const std::string& _figure_name): 
    upper(_upper), lower(_lower), left(_left), right(_right), Figure<T>(_figure_name) {}

    virtual T area() const noexcept override {
        T diag1 = Point<T>::distance(upper, lower);
        T diag2 = Point<T>::distance(left, right);

        return diag1*diag2*0.5;
    }
    virtual T perimetr() const noexcept override {
        T a = Point<T>::distance(upper, left);

        return 4.0*a;
    }
    virtual Point<T> center() const noexcept override {
        T CenterX = (upper.x + lower.x + right.x + left.x) * 0.25;
        T CenterY = (upper.y + lower.y + left.y + right.y) * 0.25;

        return Point<T>{CenterX, CenterY};
    }

    explicit virtual operator T() const noexcept override {
        return this -> area();
    }
    virtual bool operator==(const Figure<T>& other) const noexcept override {
        const Rhomb<T>* r = dynamic_cast<const Rhomb<T>*>(&other);

        if (r == nullptr) {
            return false;
        }

        return r -> upper == upper && r -> lower == lower && r -> right == right && r -> left == left;
    }
    virtual bool operator!=(const Figure<T>& other) const noexcept override {
        return !(*this == other);
    }

    friend std::ostream& operator<<(std::ostream& os, const Rhomb<T>& r) noexcept {
        return r.print(os);
    }
    friend std::istream& operator>>(std::istream& is, Rhomb<T>& r) {
        r.input(is);
        Rhomb::check(r.upper, r.lower, r.left, r.right);
        return is;
    }
};
#endif