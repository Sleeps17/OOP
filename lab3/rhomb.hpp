#ifndef PHOMB_HPP
#define PHOMB_HPP

#include"figure.hpp"
#include"point.hpp"

class Rhomb final: public Figure {

  private:
    Point upper;
    Point lower;
    Point left;
    Point right;

    static void check(const Point&, const Point&, const Point&, const Point&);

  public:
    Rhomb() = default;
    Rhomb(const Point& _upper, const Point& _lower, const Point& _left, const Point& _right, const std::string& _figure_name);
    Rhomb(const Rhomb& other) noexcept;
    virtual ~Rhomb() noexcept = default;

    virtual double area() const noexcept override;
    virtual double perimetr() const noexcept override;
    virtual Point center() const noexcept override;
    virtual void hello() const noexcept override;
    virtual void print() const noexcept override;

    explicit virtual operator double() const noexcept override;
    Rhomb& operator=(const Rhomb&) noexcept;
    Rhomb& operator=(Rhomb&&) noexcept; 
    bool operator==(const Rhomb&) const noexcept;
    bool operator!=(const Rhomb&) const noexcept;

    friend std::ostream& operator<<(std::ostream&, const Rhomb&) noexcept;
    friend std::istream& operator>>(std::istream&, Rhomb&);

};

#endif