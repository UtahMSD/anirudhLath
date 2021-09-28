//
//  main.cpp
//  Poker
//
//  Created by Anirudh Lath on 8/31/21.
//
/// Statistics of 800000 shuffles:
//  Straights:          3084 times, 0.3855%
//  Flushes:            1608 times, 0.201%
//  Full houses:        1090 times, 0.13625%
//  Straight flushes:   14 times, 0.00175%
//  Royal flushes:      1 times, 0.000125%

#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "cards.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    
    srand(int (time(NULL)));
    
    // Variables
    vector<cards> deckOfCards1 = CreateDeck(0);
    vector<cards> deckOfCards2 = CreateDeck(2);
    cards card1 = {1, "red", false, "diamonds"};
    cards card2 = {2, "red", false, "hearts"};
    cards card3 = {3, "red", false, "diamonds"};
    cards card4 = {4, "red", false, "diamonds"};
    cards card5 = {5, "red", false, "diamonds"};
    cards card6 = {10, "red", false, "diamonds"};
    cards card7 = {11, "red", false, "diamonds"};
    cards card8 = {12, "red", false, "diamonds"};
    cards card9 = {13, "red", false, "diamonds"};
    cards card10 = {2, "red", false, "diamonds"};
    int flushCount = 0;
    int straightCount = 0;
    int straightFlushCount = 0;
    int royalFlushCount = 0;
    int fullHouseCount = 0;
    int numTries = 800000;
    
    vector<cards> flush = {card1, card6, card3, card4, card5};
    vector<cards> straight = {card1, card2, card3, card4, card5};
    vector<cards> straightFlush = {card1, card10, card3, card4, card5};
    vector<cards> royalFlush = {card9, card6, card7, card8, card1};
    vector<cards> fullHouse = {card1, card1, card1, card2, card10};
    vector<cards> none = {card1, card2, card3, card3, card3};
    
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
        cout << "T2: CreateDeck() with jokers passed!" << endl;
    }
        
    
    // Test of is*() functions
    if(!isStraight(straight)){
        cout << "T3: isStraight() Failed!" << endl;
        exit(1);
    }
    else {
        cout << "T3: isStraight() Passed!" << endl;
    }
    if (!isFlush(flush)) {
        cout << "T4: isFlush() Failed!" << endl;
        exit(1);
    }
    else {
        cout << "T4: isFlush() Passed!" << endl;
    }
    if (!isStraightFlush(straightFlush)) {
        cout << "T5: isStraightFlush() Failed!" << endl;
        exit(1);
    }
    else {
        cout << "T5: isStraightFlush() Passed!" << endl;
    }
    if (!isRoyalFlush(royalFlush)) {
        cout << "T6: isRoyalFlush() Failed!" << endl;
        exit(1);
    }
    else {
        cout << "T6: isRoyalFlush() Passed!" << endl;
    }
    if (!isFullHouse(fullHouse)) {
        cout << "T7: isFullHouse() Failed!" << endl;
        exit(1);
    }
    else {
        cout << "T7: isFullHouse() Passed!" << endl;
    }
    if (isFlush(none) or isStraight(none) or isStraightFlush(none) or isRoyalFlush(none) or isFullHouse(none)) {
        cout << "T8: One of the functions failed!" << endl;
        exit(1);
    }
    else {
        cout << "T8: All functions passed!" << endl;
    }
    
    //Sort Hand Test
    ShuffleDeck(deckOfCards2);
    vector<int> sortedRanks;
    for(cards card: deckOfCards2){
        sortedRanks.push_back(card.rank);
    }
    sort(sortedRanks.begin(), sortedRanks.end());
    sortHand(deckOfCards2);
    for(int i = 0; i < deckOfCards2.size(); i++) {
        if(deckOfCards2[i].rank != sortedRanks[i]) {
            cout << "T9: sortHand() Failed!!!" << endl;
            exit(1);
        }
    }
    cout << "T9: sortHand() Passed!" << endl << endl;
    
    
    //    Deal 5 cards - Verify Console Ouput
        for (int i = 0; i < numTries; i++) {
            ShuffleDeck(deckOfCards1);
            vector<cards> cardsInHand = dealFiveCards(deckOfCards1);
            if(isStraight(cardsInHand)){
                straightCount++;
            }
            if (isFlush(cardsInHand)) {
                flushCount++;
            }
            if (isStraightFlush(cardsInHand)) {
                straightFlushCount++;
            }
            if (isRoyalFlush(cardsInHand)) {
                royalFlushCount++;
            }
            if (isFullHouse(cardsInHand)) {
                fullHouseCount++;
            }
        }
    
    //Statistics Output
    cout << "Statistics of " << numTries << " shuffles:\n";
    cout << "Straights:          " << straightCount  << " times, " << ((straightCount * 1.00000000)/numTries) * 100 << "%" << endl;
    cout << "Flushes:            " << flushCount  << " times, " << ((flushCount * 1.00000000)/numTries) * 100 << "%" << endl;
    cout << "Full houses:        " << fullHouseCount  << " times, " << ((fullHouseCount * 1.00000000)/numTries) * 100 << "%" << endl;
    cout << "Straight flushes:   " << straightFlushCount  << " times, " << ((straightFlushCount * 1.00000000)/numTries) * 100 << "%" << endl;
    cout << "Royal flushes:      " << royalFlushCount  << " times, " << ((royalFlushCount * 1.00000000)/numTries) * 100 << "%" << endl << endl;
    
    cout << "All tests passed!" << endl << endl;
    return 0;
}
