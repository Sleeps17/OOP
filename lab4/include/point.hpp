#ifndef POINT_HPP
#define POINT_HPP

#include<concepts>
#include<type_traits>
#include<complex>
#include<iostream>

template<typename T>
concept Numeric = std::is_floating_point_v<T>;

template<Numeric T>
class Point {
  
  public:
    Point() = default;
    Point(const T& _x, const T& _y): x(_x), y(_y){}
    ~Point() = default;

    bool operator==(const Point<T>& other) const noexcept {
        return abs(x - other.x) < eps && abs(y - other.y) < eps;
    }
    bool operator!=(const Point<T>& other) const noexcept {
        return !(*this == other);
    }


    friend std::ostream& operator<<(std::ostream& os, const Point<T>& point) noexcept {
        os << "(" << point.x << ", " << point.y << ")";
        return os;
    }
    friend std::istream& operator>>(std::istream& is, Point<T>& point) noexcept {
        is >> point.x >> point.y;
        return is;
    }
    static T distance(const Point<T>& p1, const Point<T>& p2) noexcept {
        T dx = p2.x - p1.x;
        T dy = p2.y - p1.y;
        return std::sqrt(dx*dx + dy*dy);
    }

  public:
    T x;
    T y;
    const constexpr static double eps = 1e-3;
};



#endif