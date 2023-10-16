#include<iostream>
#ifndef POINT_HPP
#define POINT_HPP

class Point {
  public:
    double x;
    double y;
  
    Point();
    Point(double, double);
    Point(const Point&);
    ~Point() = default;

    Point& operator=(const Point&);
    Point& operator=(Point&&);
    bool operator==(const Point&) const noexcept;

    friend std::ostream& operator<<(std::ostream&, const Point&) noexcept;
    friend std::istream& operator>>(std::istream&, Point&) noexcept;

    static double distance(const Point&, const Point&) noexcept;
};

#endif