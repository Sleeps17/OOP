#include<iostream>
#include "./include/count.hpp"

#define input_size 100
#define RED_TEXT "\033[1;31m"
#define ORANGE_TEXT "\033[1;33m"
#define GREEN_TEXT "\033[1;32m"
#define RESET_TEXT "\033[0m"


int main() {

    char* input = new char[input_size];

    while(std::cout << "Введите строку: " && std::cin.getline(input, input_size)){
        int count = count_vowels_in_word(input);

        if (count == -1) {
            std::cerr << RED_TEXT << "FATAL ERROR: input is NULL pointer" << RESET_TEXT<< '\n';
        } else if (count == -2){
            std::cerr << RED_TEXT << "ERROR: the input len is zero " << RESET_TEXT << '\n';
        } else if(count == -3) {
            std:: cerr << ORANGE_TEXT << "WARNING: input contains capital letters" << RESET_TEXT <<'\n';
        } else {
            std::cout << GREEN_TEXT << "ANS: This string contains " << count << " vowel letters" <<RESET_TEXT << '\n';
        }
    }

    std::cout << "\nEnd of input" << '\n';

    return 0;
}