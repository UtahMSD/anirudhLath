//
//  LetterHelpers.h
//  StringAnalyzer
//
//  Created by Anirudh Lath on 8/30/21.
//

#ifndef LetterHelpers_h
#define LetterHelpers_h
#include <iostream>

bool IsTerminator(char c);
bool IsPunctuation(char c);
bool IsVowel(char c);
bool IsConsonant(char c);
int NumWords(std::string str);
int NumSentences(std::string str);
int NumVowels(std::string str);
int NumConsonants(std::string str);
double AverageWordLength(std::string s);
double AverageVowelsPerWord(std::string s);


#endif /* LetterHelpers_h */
