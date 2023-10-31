#include<iostream>

#include "array.hpp"
#include "point.hpp"
#include "rhomb.hpp"
#include "trapezoid.hpp"
#include "pentagon.hpp"

int main() {

    Point<double> upper(0.0, 2.0), lower(0.0, -2.0), left(-1.0, 0.0), right(1.0, 0.0);
    Rhomb<double> r(upper, lower, left, right, "ромбик");
    std::cout << r << std::endl;    

    Point<float> left_lower(0.0, 0.0), right_lower(4.0, 0.0), left_upper(2.0, 2.0), right_upper(4.0, 2.0);
    Trapezoid<float> t(left_lower, right_lower, left_upper, right_upper, "трапеция");
    std::cout << t << std::endl;

    Point<float> left_lower2(0.0, 0.0), right_lower2(1.0, 0.0), left_upper2(-1.0, 1.0), right_upper2(2.0, 1.0), upper2(2.5, 2.0);
    Pentagone<float> p(left_lower2, right_lower2, left_upper2, right_upper2, upper2, "пятиугольник");
    std::cout << p << std::endl;
}