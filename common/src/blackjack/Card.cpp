#include<blackjack/Card.h>

namespace BlackJack {

    bool Card::isSymbolCorrect(char s)
    {
        auto it = valueMap.find(s);
        if(it != valueMap.end())
            return true;
        if(s >= '2' && s <='9')
            return true;
        return false;
    } 
    
    int Card::GetValue(){
        auto it = valueMap.find(symbol);
        if(it != valueMap.end())
            return it->second;
        return (int)(symbol - '0');
    }
    
    std::string Card::ToString() {
        return std::string() + color + symbol;
    };
    
    Card Card::FromString(std::string str)
    {
        if(str.length() != 2 || !isSymbolCorrect(str[1]))
            throw std::invalid_argument("received wrong card string format.");
            
        return Card(str[0],str[1]);
    };  
}