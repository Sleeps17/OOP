#include "figure.hpp"
#include "rhomb.hpp"
#include "trapezoid.hpp"
#include "pentagone.hpp"
#include<vector>
#include<iostream>
#include<string.h>

struct Array {

  private:
    size_t len;
    size_t cap;
    Figure** arr;

    void reallocate(size_t new_cap) {
        if (arr == nullptr) {
            return;
        }
        Figure** tmp = new Figure*[len];
        memcpy(tmp, arr, len*sizeof(Figure*));

        delete[] arr;
        arr = new Figure*[new_cap];
        memcpy(arr, tmp, len*sizeof(Figure*));
        cap = new_cap;
    }

  public:
    Array() noexcept: len(0), cap(0), arr(nullptr){}
    Array(size_t _len): len(_len), cap(len > 0 ? 2*len : 2), arr(new Figure*[cap]){}
    Array(size_t _len, size_t _cap): len(_len), cap(_cap), arr(new Figure*[cap]){}
    ~Array() noexcept {
        if (arr != nullptr) {
            delete[] arr;
            len = 0;
            cap = 0;
            arr = nullptr;
        }
    }
    void push_back(Figure* elem) {
        if (len < cap) {
            arr[len++] = elem;
            return;
        }
        this -> reallocate(2*cap);
        arr[len++] = elem;
    }
    void pop_back() {
        if (len == 0) {
            return;
        }

        len--;
    }
    void erase(size_t index) {
        if (index >= len) {
            return;
        }

        for(int i = index+1; i < len; i++) {
            arr[i-1] = arr[i];
        }
        len--;
    }
    void insert(Figure* elem, int index) {
        if(index > len || index < 0) {
            return;
        }

        if(len == cap) {
            this -> reallocate(2*cap);
        }


        len++;
        for(int i = len - 2; i >= index; i--) {
            arr[i+1] = arr[i];
        }
        arr[index] = elem;
    }

    Figure* operator[](size_t index) {
        if(index >= len) {
            return nullptr;
        }

        return arr[index];
    }
    size_t length() {
        return len;
    }
    size_t capacity() {
        return cap;
    }
};


int main() {
    Array arr(0);
    Rhomb r;
    Trapezoid t;
    Pentagone p;

    std::cin >> r;
    arr.push_back(&r);
    std::cin >> t;
    arr.push_back(&t);
    std::cin >> p;
    arr.push_back(&p);

    for(int i = 0; i < arr.length(); i++) {
        arr[i] -> hello();
        std::cout << *(arr[i]) << std::endl;
    }

    arr.erase(1);
    for(int i = 0; i < arr.length(); i++) {
        arr[i] -> hello();
        std::cout << *(arr[i]) << std::endl;
    }

    arr.insert(&t, 0);
    for(int i = 0; i < arr.length(); i++) {
        arr[i] -> hello();
        std::cout << *(arr[i]) << std::endl;
    }

}   