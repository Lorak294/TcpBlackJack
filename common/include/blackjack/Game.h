#pragma once
#include <blackjack/Card.h>
#include <vector>


namespace BlackJack {
    
    class Game {
    private:
        std::vector<Card> _deck;
        std::vector<Card> _dealersHand;
         
    };

}