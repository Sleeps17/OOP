#include<iostream>
#include "count.hpp"

#define RED_TEXT "\033[1;31m"
#define ORANGE_TEXT "\033[1;33m"
#define GREEN_TEXT "\033[1;32m"
#define RESET_TEXT "\033[0m"


int main() {

    std::string input;

    while(std::cout << "Введите строку: " && std::getline(std::cin, input)){
        int count = count_vowels_in_word(input);

        if (count == -1){
            std::cerr << RED_TEXT << "ERROR: the input len is zero " << RESET_TEXT << std::endl;
        } else if(count == -2) {
            std:: cerr << ORANGE_TEXT << "WARNING: input contains capital letters" << RESET_TEXT <<std::endl;
        } else {
            std::cout << GREEN_TEXT << "ANS: This string contains " << count << " vowel letters" <<RESET_TEXT << std::endl;
        }
    }

    std::cout << "\nEnd of input" << std::endl;

    return 0;
}