#include"pentagone.hpp"
#include<iostream>
#include<cmath>

double calculateArea(const Point& p1, const Point& p2, const Point& p3) {
    return (p1.x * (p2.y - p3.y)) +
           (p2.x * (p3.y - p1.y)) +
           (p3.x * (p1.y - p2.y));
}

void Pentagone::check(const Point& _left_lower, const Point& _left_middle, const Point& _right_lower, const Point& _right_middle, const Point& _upper) {
    double area1 = calculateArea(_left_lower, _left_middle, _right_lower);
    double area2 = calculateArea(_left_lower, _left_middle, _right_middle);
    double area3 = calculateArea(_left_lower, _left_middle, _upper);
    double area4 = calculateArea(_left_middle, _right_lower, _right_middle);
    double area5 = calculateArea(_left_middle, _right_lower, _upper);
    double area6 = calculateArea(_right_lower, _right_middle, _upper);

    if (area1 == 0 || area2 == 0 || area3 == 0 || area4 == 0 || area5 == 0 || area6 == 0) {
        throw std::invalid_argument("Points do not form a Pentagone");
    }
}

void Pentagone::print(std::ostream& os) const noexcept {
    os << "Left Lower: " << this -> left_lower << std::endl;
    os << "Right Lower: " << this -> right_lower << std::endl;
    os << "Left Middle: " << this -> left_middle << std::endl;
    os << "Right Middle: " << this -> right_middle << std::endl;
    os << "Upper: " << this -> upper << std::endl;
}
void Pentagone::input(std::istream& is) noexcept {
    std::cout << "Введите левую нижнюю точку пятиугольника: ";
    is >> this -> left_lower;
    std::cout << "Введите правую нижнюю точку пятиугольника: ";
    is >> this -> right_lower;
    std::cout << "Введите левую среднюю точку пятиугольника: ";
    is >> this -> left_middle;
    std::cout << "Введите правую среднюю точку пятиугольника: ";
    is >> this -> right_middle;
    std::cout << "Введите верхнюю точку пятиугольника: ";
    is >> this -> upper;
    std::cout << "Введите имя фигуры: ";
    is >> this -> figure_name;
}


Pentagone::Pentagone(const Point& _left_lower, const Point& _right_lower, const Point& _left_middle, const Point& _right_middle, const Point& _upper, const std::string& _figure_name):
    left_lower(Point{}),
    left_middle(Point{}),
    right_lower(Point{}),
    right_middle(Point{}),
    upper(Point{}),
    Figure(_figure_name)
{
    check(_left_lower, _right_lower, _left_middle, _right_middle, _upper);

    left_lower = _left_lower;
    left_middle = _left_middle;
    right_lower = _right_lower;
    right_middle = _right_middle;
    upper = _upper;
}
Pentagone::Pentagone(const Pentagone& other) noexcept: left_lower(other.left_lower), right_lower(other.right_lower), left_middle(other.left_middle), right_middle(other.right_middle), upper(other.upper), Figure(figure_name) {}

double Pentagone::area() const noexcept {
    return std::abs((left_lower.x*right_lower.y + right_lower.x*right_middle.y +right_middle.x*upper.y + upper.x*left_middle.y + left_middle.x*left_lower.y)
    -
    (left_lower.y*right_lower.x + right_lower.y*right_middle.x +right_middle.y*upper.x + upper.y*left_middle.x + left_middle.y*left_lower.x));
}
double Pentagone::perimetr() const noexcept {
    double a = Point::distance(left_middle, left_lower);
    double b = Point::distance(right_middle, right_lower);
    double c = Point::distance(right_lower, left_lower);
    double d = Point::distance(upper, right_middle);
    double e = Point::distance(upper, left_middle);

    return a + b + c + d + e;
}
Point Pentagone::center() const noexcept {
    double xCenter =  (left_lower.x + left_middle.x + right_lower.x + right_middle.x + upper.x)*0.2;
    double yCenter =  (left_lower.y + left_middle.y + right_lower.y + right_middle.y + upper.y)*0.2;

    return Point{xCenter, yCenter};
}
void Pentagone::hello() const noexcept {
    std::cout << "Hello, I am " << figure_name << std::endl;
}

Pentagone::operator double() const noexcept {
    return this -> area();
}
Pentagone& Pentagone::operator=(const Pentagone& other) noexcept{

    if (this != &other) {
        left_lower = other.left_lower;
        left_middle = other.left_middle;
        right_lower = other.right_lower;
        right_middle = other.right_middle;
        upper = other.upper;
    }

    return *this;
}
Pentagone& Pentagone::operator=(Pentagone&& other) noexcept {

    if (this != &other) {
        left_lower = other.left_lower;
        left_middle = other.left_middle;
        right_lower = other.right_lower;
        right_middle = other.right_middle;
        upper = other.upper;
    }

    return *this;
}
bool Pentagone::operator==(const Figure& other) const noexcept {
    const Pentagone* p = dynamic_cast<const Pentagone*>(&other);
    if (p == nullptr) {
        return false;
    }
    return left_lower == p -> left_lower && 
    left_middle == p -> left_middle && 
    right_lower == p -> right_lower && 
    right_middle == p -> right_middle && 
    upper == p -> upper;
}
bool Pentagone::operator!=(const Figure& other) const noexcept {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const Pentagone& pent) noexcept {
    pent.print(os);
    return os;
}
std::istream& operator>>(std::istream& is, Pentagone& pent) {
    pent.input(is);
    Pentagone::check(pent.left_lower, pent.right_lower, pent.left_middle, pent.right_middle, pent.upper);
    return is;
}