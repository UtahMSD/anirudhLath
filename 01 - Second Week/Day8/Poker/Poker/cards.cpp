//
//  cards.cpp
//  Poker
//
//  Created by Anirudh Lath on 8/31/21.
//

#include "cards.hpp"
#include <iostream>
#include <cstdlib>
#include <time.h>

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
        card.joker = false;
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
            joker.rank = 0;
            joker.house = "";
            joker.color = "";
            deckOfCards.push_back(joker);
        }
    }
    return deckOfCards;
}

void PrintDeck(vector<cards> deck){
    
    //Iterate the deck
    for(cards card: deck){
        if (!card.joker) {
            if(card.house == "spades"){
                card.house = "♠";
            } else if(card.house == "hearts"){
                card.house = "♥";
            } else if(card.house == "diamonds"){
                card.house = "♦";
            } else if(card.house == "clubs"){
                card.house = "♣";
            }
            if (card.rank == 11) {
                cout << "J " << card.house << " of color " << card.color << endl;
            } else if (card.rank == 12) {
                cout << "Q " << card.house << " of color " << card.color << endl;
            } else if (card.rank == 13) {
                cout << "K " << card.house << " of color " << card.color << endl;
            } else if (card.rank == 1) {
                cout << "A " << card.house << " of color " << card.color << endl;
            } else {
                cout << card.rank << " " << card.house << " of color " << card.color << endl;
            }
        }
        //Check for Jokers
        else if (card.joker) {
            cout << "Joker" << endl;
        }
        
    }
}

void ShuffleDeck(vector<cards> & deck){
    // For Loop iterate every card and swaps it with a random card.
    for(int i = deck.size() - 1; i > 0; i-- ){
        int random = (rand() % (deck.size() - 1));
        int x = i;
        cards card = deck[i];
        deck[x] = deck[random];
        deck[random] = card;
    }
}

vector<cards> dealFiveCards(vector<cards> deck) {
    //This function deals top 5 cards of a given deck.
    vector<cards> cardsInHand;
    for (int i = 0; i < 5; i++) {
        cardsInHand.push_back(deck[i]);
    }
    return cardsInHand;
}

bool isFlush(vector<cards> cardsInHand) {
    // Checks if given deck is flush or not.
    for (int i = 0; i < cardsInHand.size() - 1; i++) {        
        int r = i + 1;
        if (cardsInHand[i].house != cardsInHand[r].house) {
            return false;
        }
    }
    return true;
}

bool isStraight(vector<cards> cardsInHand) {
    // Checks if given deck is straight or not.
    vector<int> numStack;
    
    for(cards card: cardsInHand){
        numStack.push_back(card.rank);
    }
    
    sort(numStack.begin(), numStack.end());
    if(numStack[0] == 1 and numStack[1] == 10){
        numStack[0] = 14;
    }
    sort(numStack.begin(), numStack.end());
    
    for(int i = 0; i < numStack.size() - 1; i++){
        int r = i + 1;
        int check = numStack[r] - 1;
        if(numStack[i] != check){
            return false;
        }
    }
    return true;
}

bool isStraightFlush(vector<cards> cardsInHand) {
    // Checks if given deck is straight flush or not.
    vector<int> numStack;
    
    for(cards card: cardsInHand){
        numStack.push_back(card.rank);
    }

    sort(numStack.begin(), numStack.end());
    if(numStack[0] == 1 and numStack[1] == 10){
        numStack[0] = 14;
    }
    sort(numStack.begin(), numStack.end());
    
    if (isFlush(cardsInHand) and isStraight(cardsInHand)) {
        return true;
    }
    return false;
}

bool isRoyalFlush(vector<cards> cardsInHand) {
    // Checks if given deck is royal flush or not.
    vector<int> numStack;
    
    for(cards card: cardsInHand){
        numStack.push_back(card.rank);
    }

    sort(numStack.begin(), numStack.end());
    if(numStack[0] == 1 and numStack[1] == 10){
        numStack[0] = 14;
    }
    sort(numStack.begin(), numStack.end());
    
    
    if (isStraightFlush(cardsInHand) and numStack[0] == 10) {
        return true;
    }
    return false;
}

bool isFullHouse(vector<cards> cardsInHand) {
    // Checks if given deck is full house or not.
    vector<int> numStack;
    bool threes = false;
    bool twos = false;
    
    for(cards card: cardsInHand){
        numStack.push_back(card.rank);
    }

    sort(numStack.begin(), numStack.end());
    
    for(int i: numStack){
        int count = 0;
        for(int j: numStack) {
            if (i == j) {
                count++;
            }
        }
        if (count == 3) {
            threes = true;
        } else if (count == 2) {
            twos = true;
        }
    }
    return threes and twos;
}
