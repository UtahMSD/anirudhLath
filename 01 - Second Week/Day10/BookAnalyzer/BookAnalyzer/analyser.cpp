//
//  main.cpp
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

int main(int argc, const char * argv[]) {
    
    
    string bookName = "mobydick.txt";
    string userWord = "This";
    
    if(argc > 2) {
        bookName = argv[1];
        userWord = argv[2];
    } else if (argc > 1) {
        bookName = argv[1];
        cout << "No search word was entered after the filename, ignoring search word statistics." << endl;
    }
    
    ifstream file(bookName);
    
    if(file.fail()){
        cout << "The file was not found. Kindly restart the program." << endl;
        exit(1);
    }
    
    book testBook = readData(file, userWord);
    printStatistics(testBook);
    
    
    
//    vector<string> bookData = readToVector(file);
//    string bookTitle = phraseExtractor(bookData, "Title:", "Author:");
//    string bookAuthor = phraseExtractor(bookData, "Author:", "Release");
//    string bookReleaseDate = phraseExtractor(bookData, "Date:");
//
//    cout << bookTitle << endl;
//    cout << bookAuthor << endl;
//    cout << bookReleaseDate << endl;
    
//    std::ifstream file("aFableForCritics.txt");
//    std::string str;
//    string word;
//    vector<string> title;
//    while (getline(file, str)) {
//        while(file >> word){
//            if (word == "Title:") {
//
//                title.push_back(word);
//            }
//        }
//    }
    
          
          
    return 0;
}
