//
//  bookHelper.cpp
//  BookAnalyzer
//
//  Created by Anirudh Lath on 9/3/21.
//

#include "bookHelper.hpp"
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <fstream>
#include <iomanip>

using namespace std;

string phraseExtractor(vector<string> data, string start, string end  = "") {
    string phrase;
    int startIndex;
    int endIndex;
    int maxRange = data.size();
    bool startState = false;
    bool endState = false;
    
    if(start != "Date:") {
        for(int i = 0; i < maxRange; i++) {
            if(data[i] == start) {
                startIndex = i;
                startState = true;
                maxRange = i + 100;
            }
            
            if(data[i] == end) {
                endIndex = i;
                endState = true;
            } else if (data[i] == "\n") {
                endIndex = i;
                endState = true;
            }
        }
        
        if(startState == true && endState == true) {
            for(int i = startIndex + 1; i < endIndex; i++) {
                if(i != endIndex - 1) {
                    phrase += data[i] + " ";
                } else {
                    phrase += data[i];
                }
            }
        } else {
            phrase = "Unknown";
        }
    } else {
        for(int i = 0; i < maxRange; i++) {
            if(data[i] == start) {
                phrase += data[i+1] + " " + data[i+2] + " " + data[i+3];
            }
        }
    }
    return phrase;
}

vector<string> readToVector(ifstream &infile) {
    vector<string> bookData;
    string word;
    while (infile >> word) {
        bookData.push_back(word);
    }
    return bookData;
}

void userWordStats(book &book1) {
    string searchWord = book1.bookData.userWord;
    userWordStat stat;
    int charCount = 0;
    
    for(int i = 0; i < book1.bookData.words.size(); i++) {
        charCount += book1.bookData.words[i].size();
        if (book1.bookData.words[i] == searchWord) {
            charCount -= book1.bookData.words[i].size();
            stat.wordsAround = book1.bookData.words[i-1] + " " + book1.bookData.words[i] + " " + book1.bookData.words[i+1];
            stat.location = (charCount * 100) / book1.bookData.totalCharacters;
            charCount += book1.bookData.words[i].size();
            book1.bookData.userWordStats.push_back(stat);
        }
    }
}


book readData(ifstream &infile, string userWord = "") {
    book book1;
    string word;
    int shortestWordLength;
    int longestWordLength;
    //vector<string> bookData = readToVector(infile);
    
    book1.bookData.userWord = userWord;
    book1.bookData.words = readToVector(infile);
    book1.bookData.totalWords = book1.bookData.words.size();
    book1.title = phraseExtractor(book1.bookData.words, "Title:", "Author:");
    book1.author = phraseExtractor(book1.bookData.words, "Author:", "Release");
    book1.releaseDate = phraseExtractor(book1.bookData.words, "Date:");
    
    shortestWordLength = book1.bookData.words[0].size();
    longestWordLength = book1.bookData.words[0].size();
    
    for(string word: book1.bookData.words) {
        book1.bookData.totalCharacters += word.size();
        if (word.size() < shortestWordLength) {
            shortestWordLength = word.size();
            book1.bookData.shortestWord = word;
        }
        if (word.size() > longestWordLength) {
            longestWordLength = word.size();
            book1.bookData.longestWord = word;
        }
    }
    userWordStats(book1);
//    book1.bookData.userWord;
//    for(userWordStat stat: book1.bookData.userWordStats) {
//        cout << stat.location << stat.wordsAround << endl;
//    }
    return book1;
}


void printStatistics(book book1) {
    cout << "Statistics for " << book1.title << " by " << book1.author << ":\n";
    cout << " Number of words: " << book1.bookData.totalWords << endl;
    cout << " Number of characters: " << book1.bookData.totalCharacters << endl;
    cout << " The shortest word is " << '"' << book1.bookData.shortestWord << '"' << ", and the longest word is " << '"' << book1.bookData.longestWord << '"' << endl;
    cout << endl;
    if (book1.bookData.userWord != "") {
        cout << "The word " << '"' << book1.bookData.userWord << '"' << " appears " << book1.bookData.userWordStats.size() << " times:\n";
        for (userWordStat stat: book1.bookData.userWordStats) {
            cout << " at " << stat.location << "%: " << '"' << stat.wordsAround << '"' << endl;
        }
        cout << endl;
    }
    
}
