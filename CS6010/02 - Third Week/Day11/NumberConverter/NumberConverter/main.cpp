//
//  main.cpp
//  NumberConverter
//
//  Created by Anirudh Lath on 9/7/21.
//

#include <iostream>
#include <cmath>
#include <cctype>
#include <stdio.h>
#include <time.h>

using namespace std;

int stringToInt(string digits, int base) {
    int result = 0;
    int size = int(digits.size());
    char character;
    int numericValue = 0;
    bool negative = false;
    if (base == 10) {
        result = stoi(digits);
    }
    
    if(digits[0] == '-' and base != 10) {
        negative = true;
    }
    
    for(int i = size - 1; i >= 0; i--) {
        if(!isalpha(digits[i])){
            character = digits[i];
            numericValue = character - '0';
        } else {
            character = tolower(digits[i]);
            numericValue = character - 'a' + 10;
        }
        
        if (base == 2) {
            //cout << digits << endl;
            if(character == '0' or character == '1'){
                result += (numericValue * pow(2, (size - 1) - i));
            } else if (character == '-'){
                continue;
            } else {
                cout << "Non-binary digits were entered in base 2. Invalid Input." << endl;
                exit(1);
            }
        } else if (base == 16) {
            if(character == '0' or
               character == '1' or
               character == '2' or
               character == '3' or
               character == '4' or
               character == '5' or
               character == '6' or
               character == '7' or
               character == '8' or
               character == '9' or
               character == 'a' or
               character == 'b' or
               character == 'c' or
               character == 'd' or
               character == 'e' or
               character == 'f'){
                result += (numericValue * pow(16, (size - 1) - i));
            } else if (character == '-'){
                continue;
            } else {
                cout << "Non-hexadecimal digits were entered in base 16. Invalid Input." << endl;
                exit(1);
            }
        }
    }
    if(negative) {
        result *= -1;
    }
    return result;
}

string intToDecimalString(int num) {
    return to_string(num);
}

string intToBinaryString(int num) {
    string result;
    bool negative = false;
    
    if (num < 0) {
        negative = true;
    }
    
    while(num != 0) {
        if(num % 2 == 0) {
            result.insert(result.begin(), '0');
        } else {
            result.insert(result.begin(), '1');
        }
        num /= 2;
    }
    
    if(negative) {
        result.insert(result.begin(), '-');
    }
    return result;
}

string intToHexidecimalString(int num) {
    string result;
    int remainder;
    bool negative = false;
    
    if (num < 0) {
        negative = true;
    }
    
    while(num != 0) {
        remainder = num % 16;
        if (remainder < 0) {
            remainder *= -1;
        }
        if(remainder < 10) {
            string number = to_string(remainder);
            result.insert(result.begin(), remainder + '0');
        } else if (remainder == 10) {
            result.insert(result.begin(), 'A');
        } else if (remainder == 11) {
            result.insert(result.begin(), 'B');
        } else if (remainder == 12) {
            result.insert(result.begin(), 'C');
        } else if (remainder == 13) {
            result.insert(result.begin(), 'D');
        } else if (remainder == 14) {
            result.insert(result.begin(), 'E');
        } else if (remainder == 15) {
            result.insert(result.begin(), 'F');
        } else {
            cout << "Fatal error occured!" << endl;
            exit(0);
        }
        num /= 16;
        
    }
    
    if(negative) {
        result.insert(result.begin(), '-');
    }
    return result;
}

int main(int argc, const char * argv[]) {
    
    srand(time(NULL));
    
    int anything = rand();
    
    // BASIC TESTING
    assert(stringToInt("12", 10) == 12);
    assert(stringToInt("-48879", 10) == -48879);
    assert(stringToInt("-1100", 2) == -12);
    assert(stringToInt("1011111011101111", 2) == 48879);
    assert(stringToInt("c", 16) == 12);
    assert(stringToInt("-BEEF", 16) == -48879);
    assert(intToBinaryString(-48879) == "-1011111011101111");
    assert(intToBinaryString(48879) == "1011111011101111");
    assert(intToHexidecimalString(-1128) == "-468");
    assert(intToHexidecimalString(1128) == "468");
    assert(intToHexidecimalString(256) == "100");
    assert(intToDecimalString(-10000) == "-10000");
    assert(intToDecimalString(10000) == "10000");
    
    // ADVANCED REVERSED TESTING
    assert(stringToInt(intToDecimalString(anything), 10) == anything);
    assert(stringToInt(intToBinaryString(anything), 2) == anything);
    assert(stringToInt(intToHexidecimalString(anything), 16) == anything);
    
    cout << "All tests passed!" << endl << endl;
    
    return 0;
}
