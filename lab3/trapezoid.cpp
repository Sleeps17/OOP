#include"trapezoid.hpp"
#include<iostream>
#include<cmath>

void Trapezoid::check(const Point& _left_lower, const Point& _right_lower, const Point& _left_upper, const Point& _right_upper) {
    double dy1 = std::abs(_left_upper.y - _right_upper.y);
    double dx1 = std::abs(_left_upper.x - _right_upper.x);

    double dy2 = std::abs(_left_lower.y - _right_lower.y);
    double dx2 = std::abs(_left_lower.x - _right_lower.x);

    if (dy1/dx1 - dy2/dx1 < eps) {
        return;
    }

    throw std::invalid_argument("Points do not from a trapezoid");
}
void Trapezoid::print(std::ostream& os) const noexcept {
    os << "Left Upper: " << this -> left_upper << std::endl;
    os << "Right Upper: " << this -> right_upper << std::endl;
    os << "Left Lower: " << this -> left_lower << std::endl;
    os << "Right Lower: " << this -> right_lower << std::endl;
    os << "Name: " << this -> figure_name << std::endl;
}
void Trapezoid::input(std::istream& is) noexcept {
    std::cout << "Введите нижнюю левую точку трапеции: ";
    is >> this -> left_upper;
    std::cout << "введите нижнюю правую точку трапеции: ";
    is >> this -> right_upper;
    std::cout << "введите верхнюю левую точку трапеции: ";
    is >> this -> left_lower;
    std::cout << "введите верхнюю правую точку трапеции: ";
    is >> this -> right_lower;
    std::cout << "Введите имя фигуры: ";
    is >> this -> figure_name;
}


Trapezoid::Trapezoid(const Point& _left_lower, const Point& _right_lower, const Point& _left_upper, const Point& _right_upper, const std::string& _figure_name): 
    left_lower(Point{}), 
    right_lower(Point{}),  
    left_upper(Point{}), 
    right_upper(Point{}),
    Figure(_figure_name)
{
    check(_left_lower, _right_lower, _left_upper, _right_upper);

    left_lower = _left_lower;
    left_upper = _left_upper;
    right_lower = _right_lower;
    right_upper = _right_upper;
}
Trapezoid::Trapezoid(const Trapezoid& other) noexcept: left_lower(other.left_lower), right_lower(other.right_lower), left_upper(other.left_upper), right_upper(other.right_upper), Figure(other.figure_name) {}

double Trapezoid::area() const noexcept {

    double x = Point::distance(left_upper, left_lower);
    double y = Point::distance(right_upper, right_lower);
    double a = Point::distance(left_upper, left_lower);
    double z = Point::distance(left_lower, right_lower);

    double c = (x*x - y*y + z*z -2*a*z + a*a) / (2*(z - a));
    double h = std::sqrt(x*x - c*c);

    return (a + z)*0.5*h;
}
double Trapezoid::perimetr() const noexcept {
    double a = Point::distance(left_upper, left_lower);
    double b = Point::distance(left_upper, right_upper);
    double c = Point::distance(right_upper, right_lower);
    double d = Point::distance(right_lower, left_lower);

    return a + b + c + d;
}
Point Trapezoid::center() const noexcept {
    double xCenter = (left_lower.x + left_upper.x + right_lower.x + right_upper.x)*0.25;
    double yCenter = (left_lower.y + left_upper.y + right_lower.y + right_upper.y)*0.25;

    return Point{xCenter, yCenter};
}
void Trapezoid::hello() const noexcept {
    std::cout << "Hello, I am " << figure_name << std::endl;
}

Trapezoid::operator double() const noexcept {
    return this -> area();
}
Trapezoid& Trapezoid::operator=(const Trapezoid& other) noexcept{

    if (this != &other) {
        left_lower = other.left_lower;
        left_upper = other.left_upper;
        right_lower = other.right_lower;
        right_upper = other.right_upper;
    }

    return *this;
}
Trapezoid& Trapezoid::operator=(Trapezoid&& other) noexcept {
    if (this != &other) {
        left_lower = other.left_lower;
        left_upper = other.left_upper;
        right_lower = other.right_lower;
        right_upper = other.right_upper;
    }

    return *this;
}
bool Trapezoid::operator==(const Figure& other) const noexcept {
    const Trapezoid* t = dynamic_cast<const Trapezoid*>(&other);
    if (t == nullptr) {
        return false;
    }
    return left_lower == t -> left_lower 
    && left_upper == t -> left_upper 
    && right_lower == t -> right_lower 
    && right_upper == t -> right_upper;
}
bool Trapezoid::operator!=(const Figure& other) const noexcept {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const Trapezoid& trap) noexcept {
    trap.print(os);
    return os;
}
std::istream& operator>>(std::istream& is, Trapezoid& trap) {
    trap.input(is);
    Trapezoid::check(trap.left_lower, trap.right_lower, trap.left_upper, trap.right_upper);
    return is;
}