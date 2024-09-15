#include <map>
#include "Card.h"

const std::map<char,int> Card::valueMap ={
    {'A', 1},
    {'T', 10},
    {'K', 10},
    {'Q', 10},
    {'J', 10}
};
