//
//  cards.cpp
//  Cards
//
//  Created by Anirudh Lath on 8/31/21.
//

#include "cards.hpp"
#include <iostream>

using namespace std;

vector<cards> CreateDeck(int jokerCount){
    // Assign the variables
    cards card;
    vector<cards> deckOfCards;
    vector<string> houses = {"clubs", "diamonds", "hearts", "spades"};
    vector<int> ranks = {1,2,3,4,5,6,7,8,9,10,11,12,13};
    
    // Populate the deck
    for( string house: houses) {
        card.house = house;
        if (house == "clubs" or house == "spades") {
            card.color = "black";
        } else {
            card.color = "red";
        }
        for(int rank: ranks){
            card.rank = rank;
            deckOfCards.push_back(card);
        }
    }
    
    // Check for Jokers and populate the deck if there are any.
    if (jokerCount > 0) {
        cards joker;
        for (int j = 0; j < jokerCount; j++) {
            joker.joker = true;
            deckOfCards.push_back(joker);
        }
    }
    return deckOfCards;
}

void PrintDeck(vector<cards> deck){
    for(cards card: deck){
        if (!card.joker) {
            if (card.rank == 11) {
                cout << "Jack of " << card.house << endl;
            } else if (card.rank == 12) {
                cout << "Queen of " << card.house << endl;
            } else if (card.rank == 13) {
                cout << "King of " << card.house << endl;
            } else {
                cout << card.rank << " of " << card.house << endl;
            }
        }
        if (card.joker) {
            cout << "Joker" << endl;
        }
    }
}
