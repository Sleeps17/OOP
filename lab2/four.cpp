#include"four.hpp"
#include<string.h>
#include<iostream>

// Приватный метод для реалокации памяти под базовый массив
void Four::reallocate(const size_t& _cap){

    // Если неудается выделить память генерирует исключение
    unsigned char* copy = new unsigned char[len];
    memcpy(copy, digits, len*sizeof(unsigned char));

    delete[] digits;

    // Если неудается выделить память генерирует исключение
    digits = new unsigned char[_cap];
    memset(digits, '0', _cap*sizeof(unsigned char));
    memcpy(digits, copy, len*sizeof(unsigned char));
    cap = _cap;

    delete[] copy;
}
// Приватный метод для проверки сииволов на диапазон
void Four::check(const unsigned char _digit) const {

    if (_digit > '3' || _digit < '0') {
        throw std::invalid_argument("not a four number");
    }
}

// Кострукторы
Four::Four() noexcept : len(0), cap(0), digits(nullptr){}
Four::Four(const unsigned char* _digits)
{
    if (_digits == nullptr) {
        throw std::invalid_argument("argument cannot be nullptr");
    }
    len = strlen(reinterpret_cast<const char*>(_digits)); 
    cap = 2*len;
    // Если неудается выделить памыть генерирует исключение 
    digits = new unsigned char[cap]; 

    memset(digits, '0', cap*sizeof(unsigned char));
    for(int i = 0; i < len; i++) {
        check(_digits[i]);
    }
    for(int i = 0; i < len; ++i){
        digits[i] = _digits[len - 1 - i];
    } 
}
Four::Four(size_t _len, unsigned char fill): len(_len), cap(2*len), digits(new unsigned char[cap])
{
    check(fill);
    memset(digits, fill, cap*sizeof(unsigned char));
}
Four::Four(const std::initializer_list<unsigned char>& _digits): len(_digits.size()), cap(2*len), digits(nullptr) 
{
    if(_digits.size() == 0) {
        throw std::invalid_argument("initializer list cannot be empty");
    } else {
        digits = new unsigned char[cap];
    }

    memset(digits, '0', cap*sizeof(unsigned char));
    for(auto& elem : _digits) {
        check(elem);
    }
    int i = len - 1;
    for(auto& elem : _digits) {
        digits[i] = elem;
        i--;
    }
}
Four::Four(const std::string& str): len(str.length()), cap(2*len), digits(nullptr) 
{
    if(len == 0) {
        throw std::invalid_argument("string cannot be empty");
    } else {
        digits = new unsigned char[cap];
    }
    memset(digits, '0', cap*sizeof(unsigned char));
    for(auto& elem : str) {
        check(elem);
    }
    int i = len - 1;
    for(auto& elem : str) {
        digits[i] = elem;
        i--;
    }
    digits[len] = '\0';
}
Four::Four(const Four& other)
    : len(other.lenght()), 
      cap(other.capacity()), 
      digits(new unsigned char[cap]) 
{
    memcpy(digits, other.digits, cap*sizeof(unsigned char));
}
Four::Four(Four&& other) noexcept {
    len = other.len;
    cap = other.cap;
    digits = other.digits;

    other.len = 0;
    other.cap = 0;
    other.digits = nullptr;
}

// Деструктор
Four::~Four() noexcept {
    delete[] digits;
    len = 0;
    cap = 0;
    digits = nullptr;
}

// Арифметические операторы 
Four& Four::operator=(const Four& other) noexcept {

    if(this != &other) {
        len = other.len;
        cap = other.cap;
        digits = new unsigned char[cap];
        memcpy(digits, other.digits, cap*sizeof(unsigned char));
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
            (*this).reallocate(cap*2);
            digits[len] = '1';
            len++;
        }

    }

    return *this;
}
Four Four::operator--(int) {
    if(*this == Four{"0"}) {
        throw std::logic_error("It is impossible to perform the operation -- for the number 0");
    }
    Four copy = *this;
    --(*this);
    return copy;
}
Four& Four::operator--() {
    
    if(*this == Four{"0"}) {
        throw std::logic_error("It is impossible to perform the operation -- for the number 0");
    }

    for(int i = 0; i < len; ++i) {
        if (digits[i] == '0') {
            digits[i] = '3';
        } else {
            if (i == len - 1 && digits[i] == '1') {
                if (len == 1) {
                    digits[i] = '0';
                } else {
                    digits[i] = '\0';
                    len--;
                }
            } else {
                digits[i]--;
                break;
            }
        }
    }

    return *this;
}
Four& Four::operator+=(const Four& num) {

    if(num.len > len || len >= cap) {
        if(num.cap > cap*2) {
            (*this).reallocate(num.cap);
        } else {
            (*this).reallocate(2*cap);
        }
    }

    for(int i = 0; i < num.len; i++) {
        digits[i] += (num.digits[i] - '0');
        if (i >= len) {
            len++;
        }
    }

    int gap = 0;
    for(int i = 0; i < len; i++) {
        digits[i] += gap;

        gap = (digits[i] - '0') / 4;
        digits[i] = '0' + (digits[i] - '0')%4;
    }

    if(gap != 0) {
        digits[len] = '0' + gap;
        len++;
    }

    return (*this);
}
Four& Four::operator-=(const Four& num) {

    if(num > *this) {
        throw std::logic_error("It is impossible to perform the operation -= , because result will be less then zero");
    }

    for(int i = 0; i < num.len; i++) {

        if(digits[i] >= num.digits[i]) {
            digits[i] = '0' + (digits[i] - num.digits[i]);
        } else {
            int j = i + 1;
            while(j < len && digits[j] == '0') {
                j++;
            }
            while(j != i) {
                digits[j]--;
                j--;
                digits[j] = '0' + (digits[j] - '0') + 4;
            }

            digits[i] = '0' + (digits[i] - num.digits[i]);
        } 
    }

    while(digits[len-1] == '0' && len != 1) {
        digits[len-1] = '\0';
        len--;
    }

    return *this;

}
Four& Four::operator*=(const Four& num) {
    
    int degree = static_cast<int>(num);
    if(degree == 0 || *this == Four{"0"}) {
        if (degree == 0) {
            (*this) = Four{"0"};
        }
        return *this;
    }
    Four tmp = *this;
    while(degree > 1) {
        (*this) += tmp;
        degree--;
    }

    return *this;
}
Four& Four::operator/=(const Four& num) {

    if (num == Four{"0"}) {
        throw std::logic_error("Cannot divided by zero");
    }

    if(*this == Four{"0"}) {
        return *this;
    }
    
    Four ans{"0"};

    while((*this) >= num) {
        ++ans;
        (*this) -= num;
        //std::cout << "DIVIDE " << digits << std::endl;
    }

    (*this) = ans;
    
    return *this;
}
Four& Four::operator%=(const Four& num) {

    if (num == Four{"0"}) {
        throw std::logic_error("It is impossible to calculate the remainder of the division by zero");
    }

    while((*this) >= num) {
        (*this) -= num;
    }

    return *this;
}

// Логические операторы
bool Four::operator==(const Four& other) const noexcept {

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
bool Four::operator!=(const Four& other) const noexcept {
    return !((*this) == other);
}
bool Four::operator<(const Four& other) const noexcept {
    if (len > other.len) {
        return false;
    }

    if (len < other.len) {
        return true;
    }

    for(int i = len - 1; i >= 0; --i) {
        if(other.digits[i] < digits[i]) {
            return false;
        } else if (other.digits[i] > digits[i]) {
            return true;
        }
    }

    return (*this) != other;
}
bool Four::operator>(const Four& other) const noexcept {
    return !((*this) < other || (*this) == other);
}
bool Four::operator<=(const Four& other) const noexcept {
    return ((*this) < other) || ((*this) == other);
}
bool Four::operator>=(const Four& other) const noexcept {
    return ((*this) > other) || ((*this) == other);
}

// Операторы друзья
Four operator+(const Four& left, const Four& right) {
    Four ans  = left;
    ans += right;

    return ans;
}
Four operator-(const Four& left, const Four& right) {

    if (right > left) {
        throw std::logic_error("right operand cannot be greate then left operand");
    }

    Four ans =left;
    ans -= right;
    return ans;
}
Four operator*(const Four& left, const Four& right) {
    Four ans =left;
    ans *= right;
    return ans;
}
Four operator/(const Four& left, const Four& right) {
    Four ans =left;
    ans /= right;
    return ans;
}
Four operator%(const Four& left, const Four& right) {
    Four ans = left;
    ans %= right;
    return ans;
}
std::istream& operator>>(std::istream& is, Four& num) noexcept {
    std::string s;
    is >> s;
    num = Four{s};
    return is;
}
std::ostream& operator<<(std::ostream& os, const Four& num) noexcept {
    std::string s = static_cast<std::string>(num);

    return os << s;
}

// Операторы каста
Four::operator int() const noexcept {
    
    int res = 0;
    int multyplier = 1;
    
    for(int i = 0; i < len; i++) {
        res += (digits[i] - '0')*multyplier;
        multyplier *= 4;
    }

    return res;
}
Four::operator std::string() const noexcept {
    std::string s(len, '0');
    for(int i = len - 1; i  >= 0; --i) {
        s[len - 1 - i] = digits[i];
    }
    return s;
}

// Методы-члены
size_t Four::lenght() const noexcept {
    return this -> len;
}
size_t Four::capacity() const noexcept {
    return this -> cap;
}


