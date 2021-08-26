//
//  main.cpp
//  Palindromes
//
//  Created by Anirudh Lath on 8/26/21.
//

#include <iostream>

using namespace std;

int main(int argc, const char * argv[]) {
    
    // Variables
    string str = "";
    string reversed = "";

    // Input
    cout << "Please enter a word:\n";
    cin >> str;
    cout << endl;

    // Logic
    for (int i = str.size() - 1; i >= 0; --i) {
        reversed += str[i];
    }
    
    if (str == reversed) {
        cout << str << " is a palindrome!\n";
    } else {
        cout << str << " is NOT a palindrome!\n";
    }
    return 0;
}
