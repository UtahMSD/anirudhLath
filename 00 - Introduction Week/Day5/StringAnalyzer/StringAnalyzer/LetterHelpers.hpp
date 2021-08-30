//
//  LetterHelpers.hpp
//  StringAnalyzer
//
//  Created by Anirudh Lath on 8/30/21.
//

#ifndef LetterHelpers_hpp
#define LetterHelpers_hpp
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


#endif /* LetterHelpers_hpp */
