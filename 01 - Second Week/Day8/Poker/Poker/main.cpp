//
//  main.cpp
//  Poker
//
//  Created by Anirudh Lath on 8/31/21.
//

#include <iostream>
#include "cards.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    
    // Variables
    vector<cards> deckOfCards1 = CreateDeck(0);
    vector<cards> deckOfCards2 = CreateDeck(2);
    int seed = rand();
    cards card1 = {2, "red", false, "diamonds"};
    cards card2 = {3, "red", false, "diamonds"};
    cards card3 = {4, "red", false, "diamonds"};
    cards card4 = {5, "red", false, "diamonds"};
    cards card5 = {6, "red", false, "diamonds"};
    cards joker = {0,"",true,""};
    
    vector<cards> hand = {joker, card2, card3, card4, card5};
    
    // Testing
    if (deckOfCards1.size() != 52) {
        cout << "T1: CreateDeck() failed!!!" << endl;
        exit(1);
    } else {
        cout << "T1: CreateDeck() Passed!" << endl;
    }
    
    if (deckOfCards2.size() != 54) {
        cout << "T2: CreateDeck() failed!!!" << endl;
        exit(1);
    } else {
        cout << "T2: CreateDeck() Passed!" << endl;
    }
        
    // Print Test - Verify Console Output
    cout << endl;
    PrintDeck(deckOfCards1);
    cout << endl;
    PrintDeck(deckOfCards2);
    cout << endl;
    
    //Shuffle Test - Verify Console Ouput
    for (int i = 0; i < 20; i++) {
        ShuffleDeck(deckOfCards1, seed);
        ShuffleDeck(deckOfCards2, seed);
    }
    
    
    // Print Test - Verify Console Output
    cout << endl;
    PrintDeck(deckOfCards1);
    cout << endl;
    PrintDeck(deckOfCards2);
    cout << endl;
    
//    Shuffle Test - Verify Console Ouput
    for (int i = 0; i < 96; i++) {
        vector<cards> cardsInHand = dealFiveCards(deckOfCards1);
        PrintDeck(cardsInHand);
        if(isStraight(cardsInHand)){
            cout << "++++++++++++++++++++++ STRAIGHT!" << endl;
        }
        cout << endl;
    }

    if(isStraight(hand)){
        cout << "++++++++++++++++++++++" << endl;
    }
    
    cout << "All tests passed!" << endl;
    return 0;
}
