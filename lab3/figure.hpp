#ifndef FIGURE_HPP
#define FIGURE_HPP

#include"point.hpp"

const double eps = 0.00000001;

class Figure {

  protected:
    Figure() = default;
    Figure(const std::string&);
    virtual void print(std::ostream&) const noexcept;
    virtual void input(std::istream&) noexcept;

  public:
    virtual ~Figure() noexcept = default;
    virtual double area() const noexcept = 0;
    virtual double perimetr() const noexcept = 0;
    virtual Point center() const noexcept = 0;
    virtual void hello() const noexcept = 0;

    explicit virtual operator double() const noexcept = 0;
    virtual bool operator==(const Figure&) const noexcept;
    virtual bool operator!=(const Figure&) const noexcept;
    friend std::ostream& operator<<(std::ostream&, const Figure&) noexcept;
    friend std::istream& operator>>(std::istream&, Figure&);
  protected:
    std::string figure_name;
};


#endif