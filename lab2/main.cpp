#include<iostream>
#include"four.hpp"

int main(){
    Four number;

    std::cin >> number;

    Four result = Four("22") + number;
    
    std::cout << result << std::endl;
}
