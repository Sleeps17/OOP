#include<iostream>
#include "count.hpp"

bool is_vowel(const char& letter) {
    if (letter == 'a' || letter == 'e' || letter == 'i' || letter == 'o' || letter == 'u' || letter == 'y') {
        return true;
    }

    return false;
}

bool is_valid_input(const std::string& input) {

    int len = input.length();
    for(int i = 0; i < len; ++i) {
        if(int(input[i]) != tolower(input[i])) {
            return false;
        }
    }

    return true;
}

int count_vowels_in_word(const std::string& input) {
    int len = input.length();
    if(len == 0) {
        return -1;
    }

    if(!is_valid_input(input)) {
        return -2;
    }

    int count = 0;
    for(int i = 0; i < len; ++i) {

        if(is_vowel(input[i])) {
            count++;
        }

    }

    return count;
}