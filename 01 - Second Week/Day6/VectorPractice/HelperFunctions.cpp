//
// Created by Anirudh Lath on 8/30/21.
//

#include "HelperFunctions.hpp"
#include <iostream>
#include <vector>

using namespace std;

int sum(vector<int> sumList) {
    int result = 0;
    for(int x: sumList) {
        result += x;
    }
    return result;
}

vector<char> stringToVec(string str) {
    vector<char> chars;
    chars.reserve(str.size());
for (char i : str) {
        chars.push_back(i);
    }
    return chars;
}

vector<int> reverse(vector<int> numList){
    vector<int> reversed;
    for(int x = numList.size(); x > 0; x--) {
        reversed.push_back(numList[x - 1]);
    }
    return reversed;
}