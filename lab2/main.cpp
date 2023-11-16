#include<iostream>
#include"four.hpp"

int main(){
    Four number = Four{"20"};
    std::cout << number << std::endl;

    std::cin >> number;

    try {

        while(true) {
            Four result = Four("22") * number;
            number -= Four("22");
            std::cout << result << std::endl;
        }

    } catch(std::bad_alloc ex1) {
        std::cerr << "Ошибка при реалокации памяти. Конец программы" << std::endl;
        return 0;
    } catch(std::logic_error ex2) {
        std::cerr << "Логическая ошибка при соовершении операции. Конец программы" << std::endl;
    }
}
