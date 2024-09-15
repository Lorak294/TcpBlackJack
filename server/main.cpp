#include <iostream>
#include "Card.h"

int main(){

    std::cout << "Hello server" << std::endl;

    Card c1 = Card('K','A');
    Card c2 = Card('T','A');
    Card c3 = Card('6','A');
    std::cout << c1.ToString() << '\t' << c1.GetValue() << std::endl;
    std::cout << c2.ToString() << '\t' << c2.GetValue() << std::endl;
    std::cout << c2.ToString() << '\t' << c3.GetValue() << std::endl;
    
    return 0;
}