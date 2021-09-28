//
//  WordHelpers.cpp
//  StringAnalyzer
//
//  Created by Anirudh Lath on 8/30/21.
//

#include "WordHelpers.hpp"
#include "LetterHelpers.hpp"
#include <iostream>
using namespace std;

int NumWords(string str) {
    int wordCount = 0;
    for (int i = 0; i < str.size(); i++) {
        if (str[i] == ' '){
            wordCount++;
        }
    }
    return (wordCount + 1);
}

int NumSentences(string str) {
    int wordCount = 0;
    for (int i = 0; i < str.size(); i++) {
        if (IsTerminator(str[i])){
            wordCount++;
        }
    }
    return wordCount;
}

int NumVowels(string str) {
    int wordCount = 0;
    for (int i = 0; i < str.size(); i++) {
        if (IsVowel(str[i])){
            wordCount++;
        }
    }
    return wordCount;
}

int NumConsonants(string str) {
    int wordCount = 0;
    for (int i = 0; i < str.size(); i++) {
        if (IsConsonant(str[i])){
            wordCount++;
        }
    }
    return wordCount;
}

double AverageWordLength(string s) {
    int charCount = 0;
    
    int wordCount = NumWords(s);
    for (int i = 0; i < s.size(); i++) {
        if (!IsPunctuation(s[i])) {
            charCount++;
            if (s[i] == ' ') {
                charCount--;
            }
        }
    }
    double average = (charCount * 1.000 /wordCount * 1.000);
    return average;
}

double AverageVowelsPerWord(string s) {
    int charCount = 0;
    
    int wordCount = NumWords(s);
    for (int i = 0; i < s.size(); i++) {
        if (IsVowel(s[i])) {
            charCount++;
            }
    }
    double average = (charCount * 1.000 /wordCount * 1.000);
    return average;
}

