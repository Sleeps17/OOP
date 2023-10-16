#ifndef TRAPEZOID_HPP
#define TRAPEZOID_HPP

#include"point.hpp"
#include"figure.hpp"

class Trapezoid final: public Figure {

  private:
    Point left_lower;
    Point right_lower;
    Point left_upper;
    Point right_upper;

    static void check(const Point&, const Point&, const Point&, const Point&);

  public:
    Trapezoid() = default;
    Trapezoid(const Point& _left_lower, const Point& _right_lower, const Point&  _left_upper, const Point& _right_upper, const std::string& _figure_name);
    Trapezoid(const Trapezoid& other) noexcept;
    virtual ~Trapezoid() noexcept = default;

    virtual double area() const noexcept override;
    virtual double perimetr() const noexcept override;
    virtual Point center() const noexcept override;
    virtual void hello() const noexcept override;
    virtual void print() const noexcept override;

    explicit virtual operator double() const noexcept;
    Trapezoid& operator=(const Trapezoid&) noexcept;
    Trapezoid& operator=(Trapezoid&&) noexcept;
    bool operator==(const Trapezoid&) const noexcept;
    bool operator!=(const Trapezoid&) const noexcept;

    friend std::ostream& operator<<(std::ostream&, const Trapezoid&) noexcept;
    friend std::istream& operator>>(std::istream&, Trapezoid&);
};

#endif