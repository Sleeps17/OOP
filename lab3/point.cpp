#include"point.hpp"
#include<cmath>

Point::Point(): x(0), y(0){}
Point::Point(double _x, double _y): x(_x), y(_y){}
Point::Point(const Point& other): x(other.x), y(other.y){} 

Point& Point::operator=(const Point& other) {
    if (this != &other) {
        x = other.x;
        y = other.y;
    }

    return *this;
}

Point& Point::operator=(Point&& other) {
    if(this != &other) {
        x = other.x;
        y = other.y;

        other.x = 0;
        other.y = 0;
    }

    return *this;
}

bool Point::operator==(const Point& other) const noexcept{
    return x == other.x && y == other.y;
}

std::ostream& operator<<(std::ostream& os, const Point& point) noexcept {
    os << "x: " << point.x << " y: " << point.y;
    return os;
}

std::istream& operator>>(std::istream& is, Point& point) noexcept {
    is >> point.x >> point.y;
    return is;
}

double Point::distance(const Point& p1, const Point& p2) noexcept {
        double dx = p2.x - p1.x;
        double dy = p2.y - p1.y;
        return std::sqrt(dx*dx + dy*dy);
}