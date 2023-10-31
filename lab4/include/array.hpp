#ifndef ARRAY_HPP
#define ARRAY_HPP

#include<concepts>
#include<initializer_list>
#include<memory>

template <typename T> requires std::is_default_constructible_v<T>
class Array final {

    static const size_t defaultCapacity = 8;
  
  private:
    size_t size;
    size_t cap;
    std::shared_ptr<T[]> arr;

    void expand(size_t newCap);

  public:
    Array() = default;
    Array(size_t _size, size_t _cap);
    Array(size_t _size);
    Array(const std::initializer_list<T>& list);

    Array(const Array<T>& other);
    Array(Array<T>&& other) noexcept;
    Array<T>& operator=(const Array& other);
    Array<T>& operator=(Array<T>&& other) noexcept;
    ~Array() = default;

	void push_back(const T& elem);
    void pop_back();
    void insert(size_t index, const T& elem);
    void erase(size_t index);
    size_t length() const noexcept;
    size_t capacity() const noexcept;

    T operator[](size_t index) const;

    T* begin() const noexcept;
    T* end() const noexcept;
};

template<class T> requires std::is_default_constructible_v<T> 
void Array<T>::expand(size_t newCap) {
    std::shared_ptr<T[]> newArr;

    if(newCap <= cap) {
    return;
    }

    newArr = std::shared_ptr<T[]>(new T[newCap]);
    for(size_t i = 0; i < size; ++i) {
        newArr[i] = arr[i];
    }

    arr = newArr;
    cap = newCap;
}   

template<class T> requires std::is_default_constructible_v<T>
Array<T>::Array(size_t _size, size_t _cap): size(_size), cap(_cap), arr(std::shared_ptr<T[]>(new T[cap])) {}

template<class T> requires std::is_default_constructible_v<T>
Array<T>::Array(size_t _size): size(_size), cap(size > 0 ? 2*size : defaultCapacity), arr(std::shared_ptr<T[]>(new T[cap])) {}

template <class T> requires std::is_default_constructible_v<T>
Array<T>::Array(const std::initializer_list<T>& list): size(list.size()), cap(size > 0 ? 2*size : defaultCapacity), arr(std::shared_ptr<T[]>(new T[cap])) {
    int i = 0;
    for(const T& elem : list) {
        arr[i++] = elem;
    }
}

// Правило пяти
template <class T> requires std::is_default_constructible_v<T>
Array<T>::Array(const Array<T>& other): size(other.size), cap(other.cap), arr(std::shared_ptr<T[]>(new T[cap])) {
    for(int i = 0; i < size; ++i) {
        arr[i] = other[i];
    }
}

template <class T> requires std::is_default_constructible_v<T>
Array<T>::Array(Array<T>&& other) noexcept : size(other.size), cap(other.cap), arr(other.arr) {
    other.arr = nullptr;
    other.size = 0;
    other.cap = 0;
}

template <class T> requires std::is_default_constructible_v<T>
Array<T>& Array<T>::operator=(const Array& other){
    size = other.size;
    cap = other.cap;
    arr = std::shared_ptr<T[]>(new T[cap]);
    for(int i = 0; i < size; ++i) {
        arr[i] = other[i];
    }
    return *this;
}

template <class T> requires std::is_default_constructible_v<T>
Array<T>& Array<T>::operator=(Array<T>&& other) noexcept {
    size = other.size;
    cap = other.cap;
    arr = other.arr;

    other.arr = nullptr;
    other.size = 0;
    other.cap = 0;
    return *this;
}

// Методы
template <class T> requires std::is_default_constructible_v<T>
void Array<T>::push_back(const T& elem)  {

    if(size < cap) {
        arr[size++] = elem;
    } else {
        this -> expand(cap > 0 ? 2*cap : defaultCapacity);
        arr[size++] = elem;
    }
}

template <class T> requires std::is_default_constructible_v<T>
void Array<T>::pop_back()  {

    if(size == 0) {
        throw std::logic_error("Cannot pop_back() element from empty Array");
    }

    --size;
}

template <class T> requires std::is_default_constructible_v<T>
void Array<T>::insert(size_t index, const T& elem)  {
    if(index > size) {
        throw std::logic_error("Cannot insert Element on this position: index out of range");
    }

    if(size == cap) {
        this -> expand(cap > 0 ? 2*cap : defaultCapacity);
    }

    ++size;
    for(int i = size - 2; i >= index; --i) {
        arr[i+1] = arr[i]; 
    }
    arr[index] = elem;
}

template <class T> requires std::is_default_constructible_v<T>
void Array<T>::erase(size_t index)  {
    
    if(size == 0) {
        throw std::logic_error("Cannot pop_back() element from empty Array");
    } else if (index >= size) {
        throw std::logic_error("cannot erase from this position: index out of rage");
    } else {
        for(int i = index + 1; i < size; ++i) {
            arr[i-1] = arr[i];
        }
        --size;
    }
}

template<class T> requires std::is_default_constructible_v<T>
size_t Array<T>::length() const noexcept  {
    return size;
}

template<class T> requires std::is_default_constructible_v<T>
size_t Array<T>::capacity() const noexcept  {
    return cap;
}

// Оператор []
template <class T> requires std::is_default_constructible_v<T>
T Array<T>::operator[](size_t index) const  {
    if(index >= size) {
        throw std::logic_error("Cannot take Element from this index: index out of range");
    }

    return arr[index];
}

// Для итераторов
template <class T> requires std::is_default_constructible_v<T>
T* Array<T>::begin() const noexcept  {
    return arr.get();
}

template <class T> requires std::is_default_constructible_v<T>
T* Array<T>::end() const noexcept  {
    return arr.get() + size;
}


 

#endif