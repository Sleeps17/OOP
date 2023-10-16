#include"rhomb.hpp"
#include<cmath>
#include<iostream>

void Rhomb::check(const Point& _upper, const Point& _lower, const Point& _left, const Point& _right) {
    
    double d1 = Point::distance(_upper, _right);
    double d2 = Point::distance(_upper, _left);
    double d3 = Point::distance(_lower, _right);
    double d4 = Point::distance(_lower, _left);
    
    if (d1 != d2 || d2 != d3 || d3 != d4) {
        throw std::invalid_argument("Points do not form a rhombus");
    }
} 

Rhomb::Rhomb(const Point& _upper, const Point& _lower, const Point& _left, const Point& _right, const std::string& name): upper(_upper), lower(_lower), left(_left), right(_right), Figure(name){
    check(_upper, _lower, _left, _right);
}
Rhomb::Rhomb(const Rhomb& other) noexcept: upper(other.upper), lower(other.lower), left(other.left), right(other.right), Figure(other.figure_name){}
double Rhomb::area() const noexcept {

    double diag1 = Point::distance(upper, lower);
    double diag2 = Point::distance(left, right);

    return diag1*diag2*0.5;
}
double Rhomb::perimetr() const noexcept {
    double a = Point::distance(upper, left);

    return 4.0*a;
}
Point Rhomb::center() const noexcept {
    double CenterX = (upper.x + lower.x + right.x + left.x) * 0.25;
    double CenterY = (upper.y + lower.y + left.y + right.y)*0.25;

    return Point{CenterX, CenterY};
}
void Rhomb::hello() const noexcept {
    std::cout << "Hello, I am " << figure_name << std::endl;
}
void Rhomb::print() const noexcept {
    std::cout << *this << std::endl;
}

Rhomb::operator double () const noexcept {
    return this -> area();
}
Rhomb& Rhomb::operator=(const Rhomb& other) noexcept {
    
    if (this != &other) {
        upper = other.upper;
        lower = other.lower;
        left = other.left;
        right = other.right;
    }

    return *this;
}
Rhomb& Rhomb::operator=(Rhomb&& other) noexcept {
    
    if (this != &other) {
        upper = other.upper;
        lower = other.lower;
        left = other.left;
        right = other.right;
    }

    return *this;
}
bool Rhomb::operator==(const Rhomb& other) const noexcept {
    return upper == other.upper && lower == other.lower && right == other.right && left == other.left;
}
bool Rhomb::operator!=(const Rhomb& other) const noexcept {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const Rhomb& rhomb) noexcept {
    os << "Upper: " << rhomb.upper << std::endl;
    os << "Lower: " << rhomb.lower << std::endl;
    os << "Left: " << rhomb.left << std::endl;
    os << "Right: " << rhomb.right << std::endl;
    return os;
}
std::istream& operator>>(std::istream& is, Rhomb& rhomb) {
    std::cout << "Введите верхнюю точку ромба: ";
    is >> rhomb.upper;
    std::cout << "введите нижнюю точку ромба: ";
    is >> rhomb.lower;
    std::cout << "введите левую точку ромба: ";
    is >> rhomb.left;
    std::cout << "введите правую точку ромба: ";
    is >> rhomb.right;

    rhomb.figure_name = "rhomb";

    Rhomb::check(rhomb.upper, rhomb.lower, rhomb.left, rhomb.right);
    
    return is;
}
