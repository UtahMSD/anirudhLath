//
//  main.cpp
//  PoliStructs
//
//  Created by Anirudh Lath on 8/31/21.
//

#include <iostream>
#include <string>
#include <vector>
#include "poliStructs.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    Politician MaxJ {"Max Jones", "javacans", "federal"};
    Politician JohnA {"John Appleseed", "javacans", "state"};
    Politician AlexJ {"Alex Jones", "cplusers", "federal"};
    Politician HughJ {"Hugh Jackman", "cplusers", "state"};
    Politician AndrewD {"Andrew Druce", "cplusers", "federal"};
    Politician DaveD {"Dave Dawson", "javacans", "federal"};
    
    vector<Politician> politicians = {MaxJ, JohnA, AlexJ, HughJ, AndrewD, DaveD};
    
    
    
    for(Politician p: javacans(politicians)) {
        if (p.party == "cplusers") {
            cout << "T1: Javacans() Failed!!!" << endl;
            exit(1);
        }
    }
    cout << "T1: Javacans() Passed!" << endl;
    
    for(Politician p: federalCplusers(politicians)) {
        if (p.party == "javacans" or p.classification == "state") {
            cout << "T2: federalCplusers() Failed!!!" << endl;
            exit(1);
        }
    }
    cout << "T2: federalCplusers() Passed!" << endl;
    
    cout << "\nAll tests passed!\n\n";
    
    return 0;
}
