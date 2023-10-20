#ifndef PENTAGONE_HPP
#define PENTAGONE_HPP

#include"figure.hpp"
#include"point.hpp"

class Pentagone final: public Figure {

  protected:
    Point left_lower;
    Point right_lower;
    Point left_middle;
    Point right_middle;
    Point upper;

    static void check(const Point&, const Point&, const Point&, const Point&, const Point&);
    virtual void print(std::ostream&) const noexcept override;
    virtual void input(std::istream&) noexcept override;
  public:
    Pentagone() = default;
    Pentagone(const Point& _left_lower, const Point& _right_lower, const Point&  _left_middle, const Point& _right_middle, const Point& _upper, const std::string& _figure_name);
    Pentagone(const Pentagone& other) noexcept;
    virtual ~Pentagone() noexcept = default;

    virtual double area() const noexcept override;
    virtual double perimetr() const noexcept override;
    virtual Point center() const noexcept override;
    virtual void  hello() const noexcept override;

    explicit virtual operator double() const noexcept override;
    Pentagone& operator=(const Pentagone&) noexcept;
    Pentagone& operator=(Pentagone&&) noexcept;
    virtual bool operator==(const Figure&) const noexcept override;
    virtual bool operator!=(const Figure&) const noexcept override;

    friend std::ostream& operator<<(std::ostream&, const Pentagone&) noexcept;
    friend std::istream& operator>>(std::istream&, Pentagone&);
};

#endif