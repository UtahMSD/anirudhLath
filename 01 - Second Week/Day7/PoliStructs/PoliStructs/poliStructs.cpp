//
//  poliStructs.cpp
//  PoliStructs
//
//  Created by Anirudh Lath on 8/31/21.
//
#include <iostream>
#include <vector>
#include <string>
#include "poliStructs.hpp"

using namespace std;

vector<Politician> javacans( vector<Politician> poli) {
    vector<Politician> javacansOnly;
    for( Politician p: poli) {
        if (p.party == "javacans") {
            javacansOnly.push_back(p);
        }
    }
    return javacansOnly;
}

vector<Politician> federalCplusers( vector<Politician> poli) {
    vector<Politician> federalCplusersOnly;
    for( Politician p: poli) {
        if (p.party == "cplusers" && p.classification == "federal") {
            federalCplusersOnly.push_back(p);
        }
    }
    return federalCplusersOnly;
}
