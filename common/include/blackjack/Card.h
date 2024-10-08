#pragma once

#include <string>
#include <stdexcept>
#include <map>


namespace BlackJack {

    class Card
    {
    private:
        char symbol;
        char color;
        static const std::map<char,int> valueMap;
        
    private:
        static bool isSymbolCorrect(char s);
    
    public:
        Card(char symbol, char color) : symbol(symbol), color(color) {};
        
        std::string ToString();
        static Card FromString(std::string str);
        int GetValue();
    };
}
