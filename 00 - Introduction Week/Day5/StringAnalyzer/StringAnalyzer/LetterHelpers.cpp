//
//  LetterHelpers.cpp
//  StringAnalyzer
//
//  Created by Anirudh Lath on 8/30/21.
//

#include <stdio.h>
#include "LetterHelpers.h"
#include <iostream>
using namespace std;

bool IsTerminator(char c) {
    return (c == '.' or c == '!' or c == '?');
}

bool IsPunctuation(char c) {
    return (c == '.' or c == '!' or c == '?' or c == ',');
}

bool IsVowel(char c) {
    return (c == 'a'
    or c == 'e'
    or c == 'i'
    or c == 'o'
    or c == 'u'
    or c == 'y'
    or c == 'A'
    or c == 'E'
    or c == 'I'
    or c == 'O'
    or c == 'U'
    or c == 'Y');
}

bool IsConsonant(char c) {
    return (!IsVowel(c) and !IsPunctuation(c) and c != ' ');
}
