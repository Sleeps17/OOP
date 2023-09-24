#include"four.hpp"
#include<string.h>

Four::Four(): len(0), cap(0), digits(nullptr){}
Four::Four(const unsigned char* _digits): len(strlen(reinterpret_cast<const char*>(_digits))), cap(2*len), digits(new unsigned char[cap]){
    for(int i = 0; i < len; ++i){
        digits[i] = _digits[len - 1 - i];
    } 
}
Four::Four(const std::initializer_list<unsigned char>& _digits): len(_digits.size()), cap(2*len), digits(new unsigned char[cap]) {
    memset(digits, 1, cap);
    int i = len - 1;
    for(auto& elem : _digits) {
        digits[i] = elem;
        i--;
    }
}
Four::Four(const std::string& str): len(str.length()), cap(2*len), digits(new unsigned char[cap]) {
    memset(digits, 1, cap);
    int i = len - 1;
    for(auto& elem : str) {
        digits[i] = elem;
        i--;
    }
    digits[len] = '\0';
}
Four::Four(const Four& other): len(other.lenght()), cap(other.capacity()), digits(new unsigned char[cap]) {
    const auto& data = other.get();
    std::copy(data, data + cap, digits);
}
Four::Four(Four&& other) noexcept {
    len = other.len;
    cap = other.cap;
    digits = other.digits;

    other.len = 0;
    other.cap = 0;
    delete[] other.digits;
    other.digits = nullptr;
}

Four::~Four() {
    delete []digits;
    len = 0;
    cap = 0;
    digits = nullptr;
}

Four& Four::operator=(const Four& other) {

    if(this != &other) {
        len = other.len;
        cap = other.cap;
        digits = new unsigned char[cap];
        std::copy(other.digits, other.digits+cap, digits);
    }

    return *this;
}
Four& Four::operator=(Four&& other) noexcept{

    if(this != &other) {
        len = other.len;
        cap = other.cap;
        
        delete[] digits;
        digits = other.digits;

        other.len = 0;
        other.cap = 0;
        other.digits = nullptr;
    }

    return *this;
}
Four Four::operator++(int) {
    Four copy = *this;
    ++(*this);
    return copy;
}
Four& Four::operator++() {

    int gap = 1;

    for(int i = 0; i < len; ++i) {
        digits[i] += gap;
        gap = 0;

        if (digits[i] > '3') {
            gap += digits[i] - '3';
            digits[i] -= 4;
        }    
    }

    if (digits[len - 1] == '0') {

        if (len < cap) {
            digits[len] = '1';
            len++;
        } else {
            auto tmp = digits;
            delete[] digits;
            cap *= 2;
            digits = new unsigned char[cap];
            std::copy(tmp, tmp+len, digits);
        }

    }

    return *this;
}
Four Four::operator--(int) {
    //добавить проверку на ноль и если что кидать exeption
    Four copy = *this;
    --(*this);
    return copy;
}
Four& Four::operator--() {
    
    //Добавить проверку на ноль и если что кидать exeption

    for(int i = 0; i < len; ++i) {
        if (digits[i] == '0') {
            digits[i] = '3';
        } else {
            if (i == len - 1 && digits[i] == '1') {
                digits[i] = 1;
                break;
            } else {
                digits[i]--;
                break;
            }
        }
    }

    return *this;
}


bool Four::operator==(const Four& other) {

    if (len != other.len) {
        return false;
    }

    for(int i = 0; i < len; i++) {
        if(digits[i] != other.digits[i]) {
            return false;
        }
    }

    return true;
}
bool Four::operator!=(const Four& other) {
    return !((*this) == other);
}
bool Four::operator<(const Four& other) {
    if (len > other.len) {
        return false;
    }

    if (len < other.len) {
        return true;
    }

    for(int i = len - 1; i >= 0; --i) {
        if(other.digits[i] < digits[i]) {
            return false;
        }
    }

    return (*this) != other;
}
bool Four::operator>(const Four& other) {
    return !((*this) < other || (*this) == other);
}
bool Four::operator<=(const Four& other) {
    return ((*this) < other) || ((*this) == other);
}
bool Four::operator>=(const Four& other) {
    return ((*this) > other) || ((*this) == other);
}

std::ostream& operator<<(std::ostream& os,  const Four& num){
    
  for(int i = num.len - 1; i >= 0; --i) {
    os << num.digits[i];
  }

  return os;
}
std::istream& operator>>(std::istream& in, Four& num) {
    std::string s;
    in >> s;
    num = Four{s};
    return in;
}

unsigned char* Four::get() const {
    return this->digits;
}
size_t Four::lenght() const {
    return this -> len;
}
size_t Four::capacity() const {
    return this -> cap;
}


