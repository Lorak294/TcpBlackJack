#include <iostream>
#include "Card.h"

int main(){
    std::cout << "Hello client" << std::endl;

        Card c = Card('T','C');
    std::cout << c.ToString() << std::endl;
    return 0;
}