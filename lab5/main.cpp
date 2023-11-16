#include<iostream>
#include<chrono>
#include<map>
#include<forward_list>
#include<type_traits>

#include"allocator.hpp"
#include"forward_list.hpp"

const int max_count = 100;

template<typename T, typename U>
using my_map_allocator = lab::Allocator<std::pair<const T, U>, max_count>;

template<typename T, typename U>
using my_map = std::map<T, U, std::less<T>, my_map_allocator<T, U>>;

template<typename T>
using my_forward_list_allocator = lab::Allocator<lab::Node<T>, max_count>;

template<typename T>
using my_forward_list = lab::forward_list<T, std::allocator<lab::Node<T>>>;

template <int N>
struct Factorial {
    static const int value = N * Factorial<N - 1>::value;
};

template <>
struct Factorial<0> {
    static const int value = 1;
};

template<int N>
void makeMap(my_map<int, int>& m) {
    m[N] = Factorial<N>::value;
    makeMap<N-1>(m);
}

template<>
void makeMap<0>(my_map<int, int>& m) {
    m[0] = 1;
}

template<typename T>
void print(const my_forward_list<T>& f) {
    std::cout << "_________________\n";
    for(auto elem : f) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

int main() {
    my_map<int, int> m;
    makeMap<10>(m);


    for(int i = 0; i < 10; i++) {
        std::cout << i << " : " << m[i] << std::endl;
    }

    my_forward_list<int> f = {1, 2, 3, 4, 5, 6, 7, 8};
    print(f);
}