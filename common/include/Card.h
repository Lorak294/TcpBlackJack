#pragma once
#include <string>
#include <stdexcept>
#include <map>

class Card
{
private:
    char symbol;
    char color;
    static const std::map<char,int> valueMap;
    
public:
    Card(char symbol, char color) : symbol(symbol), color(color) {};
    
    std::string ToString() {
        return std::string() + color + symbol;
    };
    static Card FromString(std::string str)
    {
        if(str.length() != 2 || !IsSymbolCorrect(str[1]))
            throw std::invalid_argument("received wrong card string format.");
        
        return Card(str[0],str[1]);
    };
    
    int GetValue(){
        auto it = valueMap.find(symbol);
        if(it != valueMap.end())
            return it->second;
        return (int)(symbol - '0');
    }

    static bool IsSymbolCorrect(char s)
    {
        auto it = valueMap.find(s);
        if(it != valueMap.end())
            return true;
        if(s >= '2' && s <='9')
            return true;
        return false;
    }
};