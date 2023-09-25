#include"four.hpp"
#include<string.h>
#include<exception>
#include<algorithm>

// Приватный метод для реалокации памяти под базовый массив
void Four::reallocate(const size_t& _cap){
    unsigned char* copy = new unsigned char[cap];
    memcpy(copy, digits, cap*sizeof(unsigned char));

    delete[] digits;

    digits = new unsigned char[_cap];
    memset(digits, 1, _cap);
    memcpy(digits, copy, cap*sizeof(unsigned char));
    delete[] copy;
    cap = _cap;
}

// Кострукторы
Four::Four(): len(0), cap(0), digits(nullptr){}
Four::Four(const unsigned char* _digits)
    : len(strlen(reinterpret_cast<const char*>(_digits))), 
      cap(2*len), 
      digits(new unsigned char[cap]) 
{
    for(int i = 0; i < len; ++i){
        digits[i] = _digits[len - 1 - i];
    } 
}
Four::Four(const std::initializer_list<unsigned char>& _digits)
    : len(_digits.size()), 
      cap(2*len), 
      digits(new unsigned char[cap]) 
{
    memset(digits, 1, cap);
    int i = len - 1;
    for(auto& elem : _digits) {
        digits[i] = elem;
        i--;
    }
}
Four::Four(const std::string& str)
    : len(str.length()), 
      cap(2*len), 
      digits(new unsigned char[cap]) 
{
    memset(digits, 1, cap);
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
    std::copy(other.digits, other.digits + cap, digits);
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
Four::~Four() {
    delete[] digits;
    len = 0;
    cap = 0;
    digits = nullptr;
}

// Арифметические операторы 
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
            (*this).reallocate(cap*2);
            digits[len] = '1';
            len++;
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
Four& Four::operator+=(const Four& num) {

    if (num.len > cap) {
        (*this).reallocate(num.cap);
    }

    for(int i = 0; i < num.len; i++) {
        digits[i] += (num.digits[i] - '0');
    }

    int gap = 0;
    for(int i = 0; i < len; i++) {
        digits[i] += gap;

        gap = (digits[i] - '0') / 4;
        digits[i] = '0' + (digits[i] - '0')%4;
    }

    return (*this);
}
Four& Four::operator-=(const Four& num) {

    // Если num > *this кинуть исключение

    for(int i = 0; i < num.len; i++) {

        if(digits[i] >= num.digits[i]) {
            digits[i] = '0' + (digits[i] - num.digits[i]);
        } else {
            digits[i+1]--;
            digits[i] = '0' + (((digits[i] - '0') + 4) - (num.digits[i] - '0'));
        } 
    }

    if (digits[len - 1] == '0') {
        digits[len-1] = '\0';
        len--;
    }

    return *this;

}
Four& Four::operator*=(const Four& num) {
    
    int degree = static_cast<int>(num);
    while(degree > 1) {
        (*this) += (*this);
        degree--;
    }

    return *this;
}
Four& Four::operator/=(const Four& num) {
    
    Four ans{"0"};

    while((*this) > num) {
        ans++;
        (*this) -= num;
    }

    (*this) = ans;
    
    return *this;
}
Four& Four::operator%=(const Four& num) {

    while((*this) >= num) {
        (*this) -= num;
    }

    return *this;
}

// Логические операторы
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

// Операторы друзья
Four operator+(const Four& left, const Four& right) {
    Four ans = left;
    ans += right;

    return ans;
}
Four operator-(const Four& left, const Four& right) {

    //Не забыть про exeption

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
std::istream& operator>>(std::istream& is, Four& num) {
    std::string s;
    is >> s;
    num = Four{s};
    return is;
}
std::ostream& operator<<(std::ostream& os, const Four& num) {
    std::string s = static_cast<std::string>(num);

    reverse(s.begin(), s.end());

    return os << s;
}

// Операторы каста
Four::operator int() const{
    
    int res = 0;
    int multyplier = 1;
    
    for(int i = 0; i < len; i++) {
        res += (digits[i] - '0')*multyplier;
        multyplier *= 4;
    }

    return res;
}
Four::operator std::string() const {
    std::string s{reinterpret_cast<const char*>(digits)};
    return s;
}

// Методы-члены
unsigned char* Four::get() const {
    return this->digits;
}
size_t Four::lenght() const {
    return this -> len;
}
size_t Four::capacity() const {
    return this -> cap;
}


