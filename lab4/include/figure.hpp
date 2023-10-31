#ifndef FIGURE_HPP
#define FIGURE_HPP

#include <type_traits>
#include "point.hpp"

template <Numeric T>
class Figure {

  protected:
    Figure() = default;
    Figure(const std::string& str): figure_name(str) {}
    virtual std::ostream& print(std::ostream& os) const noexcept {
        return os << this -> figure_name;
    }
    virtual std::istream& input(std::istream& is) noexcept {
        return is >> this -> figure_name;
    }

  public:
    virtual ~Figure() noexcept = default;
    virtual T area() const noexcept = 0;
    virtual T perimetr() const noexcept = 0;
    virtual Point<T> center() const noexcept = 0;

    explicit virtual operator T() const noexcept = 0;
    virtual bool operator==(const Figure& other) const noexcept {
        return this -> figure_name == other.figure_name;
    }
    virtual bool operator!=(const Figure& other) const noexcept {
        return this -> figure_name != other.figure_name;
    }
    friend std::ostream& operator<<(std::ostream& os, const Figure& f) noexcept {
        return f.print(os);
    }
    friend std::istream& operator>>(std::istream& is, Figure& f) {
        return f.input(is);
    }
  
  protected:
    std::string figure_name;
    
};

#endif