//
//  cards.hpp
//  Cards
//
//  Created by Anirudh Lath on 8/31/21.
//

#ifndef cards_hpp
#define cards_hpp

#include <stdio.h>
#include <string>
#include <vector>

struct cards {
    int rank;
    std::string color;
    bool joker;
    std::string house;
};

std::vector<cards> CreateDeck(int jokerCount);
void PrintDeck(std::vector<cards> deck);

#endif /* cards_hpp */
