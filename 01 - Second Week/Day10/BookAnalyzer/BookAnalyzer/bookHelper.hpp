//
//  bookHelper.hpp
//  BookAnalyzer
//
//  Created by Anirudh Lath on 9/3/21.
//

#ifndef bookHelper_hpp
#define bookHelper_hpp

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <fstream>
#include <iomanip>

struct userWordStat {
    int location;
    std::string wordsAround;
    
};

struct content {
    std::vector<std::string> words;
    int totalWords;
    int totalCharacters;
    std::string userWord;
    std::string shortestWord;
    std::string longestWord;
    std::vector<userWordStat> userWordStats;
    
};

struct book {
    content bookData;
    std::string title;
    std::string author;
    std::string releaseDate;
    
};

book readData(std::ifstream &infile, std::string userWord);
void printStatistics(book book1);

#endif /* bookHelper_hpp */
