#ifndef FIGURE_HPP
#define FIGURE_HPP

#include<string_view>
#include"point.hpp"

const double eps = 0.00000001;

class Figure {

  protected:
    Figure() = default;
    Figure(const std::string&);

  public:
    virtual ~Figure() noexcept = default;
    virtual double area() const noexcept = 0;
    virtual double perimetr() const noexcept = 0;
    virtual Point center() const noexcept = 0;
    virtual void hello() const noexcept = 0;
    virtual void print() const noexcept = 0;

    explicit virtual operator double() const noexcept = 0;
  protected:
    std::string figure_name;
};


#endif