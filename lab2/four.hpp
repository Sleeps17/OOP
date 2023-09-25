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
  
  public:
    // Конструкторы
    Four();
    Four(const unsigned char*);
    Four(const std::initializer_list<unsigned char>&);
    Four(const std::string&);
    Four(const Four&);
    Four(Four&&) noexcept;

    // Деструктор
    virtual ~Four() noexcept;

    // Опрераторы-члены
    Four& operator=(const Four&);
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

    // Операторы друзья
    friend Four operator+(const Four&, const Four&);
    friend Four operator-(const Four&, const Four&);
    friend Four operator*(const Four&, const Four&);
    friend Four operator/(const Four&, const Four&);
    friend Four operator%(const Four&, const Four&);
    friend std::istream& operator>>(std::istream&, Four&);
    friend std::ostream& operator<<(std::ostream&,  const Four&);

    // Логические операторы
    bool operator==(const Four&);
    bool operator!=(const Four&);
    bool operator<(const Four&);
    bool operator>(const Four&);
    bool operator<=(const Four&);
    bool operator>=(const Four&);

    // Операторы каста
    operator int() const;
    operator std::string() const;

    // Методы-члены 
    unsigned char* get() const;
    size_t lenght() const;
    size_t capacity() const;

};

#endif