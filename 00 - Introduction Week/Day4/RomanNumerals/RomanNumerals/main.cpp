//
//  main.cpp
//  RomanNumerals
//
//  Created by Anirudh Lath on 8/26/21.
// I didn't think this will work but it did so I am surprised :)

#include <iostream>

using namespace std;

int main(int argc, const char * argv[]) {
    // Variables
    int num;
    string roman;
    
    // Input
    cout << "Please enter a number:\n";
    cin >> num;
    cout << endl;
    
    // Error Handling
    if (num < 0) {
        cout << "\nInvalid Input. Please try again.\n\n";
    } else if (num == 0) {
        cout << "\nI don't think there is a roman numeral for 0. Please try again.\n\n";
    }
    
    while (num <= 0) {
        cout << "Please enter a number:\n";
        cin >> num;
        cout << endl;
    }
    
    //Logic
    while (num > 0) {
        if (num >= 1000) {
            roman += "M";
            num = abs(num - 1000);
        }
        else if (num >= 900) {
            roman += "CM";
            num = abs(num - 900);
        }
        else if (num >= 500) {
            roman += "D";
            num = abs(num - 500);
        }
        else if (num >= 400) {
            roman += "CD";
            num = abs(num - 400);
        }
        else if (num >= 100) {
            roman += "C";
            num = abs(num - 100);
        }
        else if (num >= 90) {
            roman += "XC";
            num = abs(num - 90);
        }
        else if (num >= 50) {
            roman += "L";
            num = abs(num - 50);
        }
        else if (num >= 40) {
            roman += "XL";
            num = abs(num - 40);
        }
        else if (num >= 10) {
            roman += "X";
            num = abs(num - 10);
        }
        else if (num >= 9) {
            roman += "IX";
            num = abs(num - 9);
        }
        else if (num >= 5) {
            roman += "V";
            num = abs(num - 5);
        }
        else if (num >= 4) {
            roman += "IV";
            num = abs(num - 4);
        }
        else if (num >= 1) {
            roman += "I";
            num = abs(num - 1);
        }
    }
    
    cout << "Roman numeral for the number you have entered is:\n" << roman << endl << endl;
    
    return 0;
}
