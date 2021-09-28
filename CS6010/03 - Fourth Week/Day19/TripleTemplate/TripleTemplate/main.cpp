//
//  main.cpp
//  TripleTemplate
//
//  Created by Anirudh Lath on 9/17/21.
//

#include <iostream>
#include <vector>
#include "Triple.h"

using namespace std;

int main(int argc, const char * argv[]) {
    
    
    // Type <int>
    Triple<int> tripleInt;
    
    tripleInt.a = 1;
    tripleInt.b = 2;
    tripleInt.c = 3;
    
    cout << "Sum of Ints: " << tripleInt.sum() << endl;
    
    // Type <string>
    Triple<string> tripleString;
    
    tripleString.a = " a ";
    tripleString.b = " b ";
    tripleString.c = " c ";
    
    cout << "Sum of strings: " << tripleString.sum() << endl;
    
    // Type <vector<int>>
    Triple<vector<int>> tripleVectorInt;
    
    tripleVectorInt.a.push_back(4);
    tripleVectorInt.b.push_back(2);
    tripleVectorInt.c.push_back(3);
    
//    tripleVectorInt.sum();
    
    // The sum method doesn't work with the vector<int> and causes error in the program.
    
    
    
    return 0;
}
