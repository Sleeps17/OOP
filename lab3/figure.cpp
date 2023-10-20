#include"figure.hpp"

Figure::Figure(const std::string& v): figure_name(v){}
void Figure::input(std::istream& is) noexcept {
    is >> this -> figure_name;
}
void Figure::print(std::ostream& os) const noexcept {
    os << this -> figure_name;
}


bool Figure::operator==(const Figure& f) const noexcept {
    return this -> figure_name == f.figure_name;
}
bool Figure::operator!=(const Figure& f) const noexcept {
    return !(*this == f);
}
std::ostream& operator<<(std::ostream& os, const Figure& f) noexcept {
    f.print(os);
    return os;
}
std::istream& operator>>(std::istream& is, Figure& f) {
    f.input(is);
    return is;
}
