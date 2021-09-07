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

// Created a function to extract string between to given words. Assigned a default value to avoid errors if the next keyword is not found.
string phraseExtractor(vector<string> data, string start, string end  = "") {
    string phrase;
    int startIndex = 0;
    int endIndex = 0;
    int maxRange = int(data.size());
    bool startState = false;
    bool endState = false;
    // Date algorithm is different therefore saving that for another bool check.
    if(start != "Date:") {
        for(int i = 0; i < maxRange; i++) {
            if(data[i] == start) {
                startIndex = i;
                endIndex = i;
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
        
        if(startState == true && endState == true) { //If any of the states are false, "Unknown" will be assigned to the search element.
            for(int i = startIndex + 1; i < endIndex; i++) {
                if(i != endIndex - 1) {
                    phrase += data[i] + " ";
                } else { // Don't add space if it is the last word.
                    phrase += data[i];
                }
            }
        } else {
            phrase = "Unknown";
        }
    } else { //Date algorithm
        for(int i = 0; i < maxRange; i++) {
            if(data[i] == start) {
                phrase += data[i+1] + " " + data[i+2] + " " + data[i+3];
            }
        }
    }
    return phrase;
}

// Add all words to a vector.
vector<string> readToVector(ifstream &infile) {
    vector<string> bookData;
    string word;
    while (infile >> word) {
        bookData.push_back(word);
    }
    return bookData;
}

// Prepare search word statistics
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
    
    //Prepare book and content data structure.
    book1.bookData.userWord = userWord;
    book1.bookData.words = readToVector(infile);
    book1.bookData.totalWords = int(book1.bookData.words.size());
    book1.title = phraseExtractor(book1.bookData.words, "Title:", "Author:");
    book1.author = phraseExtractor(book1.bookData.words, "Author:", "Release");
    book1.releaseDate = phraseExtractor(book1.bookData.words, "Date:");
    
    shortestWordLength = int(book1.bookData.words[0].size());
    longestWordLength = int(book1.bookData.words[0].size());
    book1.bookData.shortestWord = book1.bookData.words[0];
    book1.bookData.longestWord = book1.bookData.words[0];
    
    for(string word: book1.bookData.words) {
        book1.bookData.totalCharacters += word.size();
        if (word.size() < shortestWordLength && isalpha(word[0])) {
            shortestWordLength = int(word.size());
            book1.bookData.shortestWord = word;
        }
        if (word.size() > longestWordLength && isalpha(word[0])) {
            longestWordLength = int(word.size());
            book1.bookData.longestWord = word;
        }
    }
    userWordStats(book1); // Prepare userWordStat struct and populate book.content.userWordStats
    return book1;
}

// Create a print function for ease of use and clean main() structure.
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
