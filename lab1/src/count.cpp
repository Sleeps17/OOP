#include<stdlib.h>
#include<string.h>
#include<iostream>
#include "../include/count.hpp"

bool is_vowel(char letter) {
    if (letter == 'a' || letter == 'e' || letter == 'i' || letter == 'o' || letter == 'u') {
        return true;
    }

    return false;
}

bool is_valid_input(const char* input) {

    int len = strlen(input);
    for(int i = 0; i < len; ++i) {
        if(int(input[i]) != tolower(input[i])) {
            return false;
        }
    }

    return true;
}

int count_vowels_in_word(const char* input) {
    if(input == NULL) {
        return -1;
    }

    int len = strlen(input);
    if(len == 0) {
        return -2;
    }

    if(!is_valid_input(input)) {
        return -3;
    }

    int count = 0;
    for(int i = 0; i < len; ++i) {

        if(is_vowel(input[i])) {
            count++;
        }

    }

    return count;
}