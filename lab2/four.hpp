#ifndef FOUR_HPP
#define FOUR_HPP
#include<string>

class Four {
  private:
    size_t len;
    size_t cap;
    unsigned char* digits;

    // Приватный метод для реалокации памяти под базовый массив
    void reallocate(const size_t&);
    // Приватный  метод для проверки сивола на то, принадлежит ли он четверичной сис.счисления или нет
    void check(const unsigned char) const;
  
  public:
    // Конструкторы
    Four() noexcept;
    Four(size_t, unsigned char);
    Four(const unsigned char*);
    Four(const std::initializer_list<unsigned char>&);
    Four(const std::string&);
    Four(const Four&);
    Four(Four&&) noexcept;

    // Деструктор
    virtual ~Four() noexcept;

    // Опрераторы-члены
    Four& operator=(const Four&) noexcept;
    Four& operator=(Four&&) noexcept;
    Four operator++(int);
    Four& operator++();
    Four operator--(int);
    Four& operator--();
    Four& operator+=(const Four&);
    Four& operator-=(const Four&);
    Four& operator*=(const Four&);
    Four& operator/=(const Four&);
    Four& operator%=(const Four&);

    // Логические операторы
    bool operator==(const Four&) const noexcept;
    bool operator!=(const Four&) const noexcept;
    bool operator<(const Four&) const noexcept;
    bool operator>(const Four&) const noexcept;
    bool operator<=(const Four&) const noexcept;
    bool operator>=(const Four&) const noexcept;

    // Операторы друзья
    friend Four operator+(const Four&, const Four&);
    friend Four operator-(const Four&, const Four&);
    friend Four operator*(const Four&, const Four&);
    friend Four operator/(const Four&, const Four&);
    friend Four operator%(const Four&, const Four&);
    friend std::istream& operator>>(std::istream&, Four&) noexcept;
    friend std::ostream& operator<<(std::ostream&,  const Four&) noexcept;

    // Операторы каста
    operator int() const noexcept;
    operator std::string() const noexcept;

    // Методы-члены 
    size_t lenght() const noexcept;
    size_t capacity() const noexcept;

};

#endif