//
//  main.cpp
//  Cards
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
    
    
    // Print Test - Verify console output
    cout << endl;
    PrintDeck(deckOfCards1);
    cout << endl;
    PrintDeck(deckOfCards2);
    cout << endl;
    cout << "All tests passed!" << endl;
    
    return 0;
}
