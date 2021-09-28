//
//  WordHelpers.hpp
//  StringAnalyzer
//
//  Created by Anirudh Lath on 8/30/21.
//

#ifndef WordHelpers_hpp
#define WordHelpers_hpp

#include <stdio.h>

#include <iostream>

int NumWords(std::string str);
int NumSentences(std::string str);
int NumVowels(std::string str);
int NumConsonants(std::string str);
double AverageWordLength(std::string s);
double AverageVowelsPerWord(std::string s);

#endif /* WordHelpers_hpp */
