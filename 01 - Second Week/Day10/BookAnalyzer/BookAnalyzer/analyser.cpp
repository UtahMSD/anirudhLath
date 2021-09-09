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
    
    // Variables
    string bookName = "";
    string userWord = "";
    int encodeKey = 0;
    string encodedBookName = "";
    bool encode = false;
    
    // Command Line Arguments
    if(argc > 2) {
        bookName = argv[1];
        userWord = argv[2];
        if( userWord == "-encode" and argc == 4) {
            encodeKey = stoi(argv[3]);
            userWord = "";
            encode = true;
            for(char c: bookName) {
                if(c == '.') {
                    break;
                }
                encodedBookName.push_back(c);
            }
            encodedBookName += "_encoded.txt";
        } else if ( userWord == "-encode" and argc != 4) {
            cout << "Please enter encode key after '-encode' to proceed with the program. Program will now exit, please re-run." << endl;
            exit(1);
        }
    } else if (argc > 1) {
        bookName = argv[1];
        cout << "No search word was entered after the filename, ignoring search word statistics." << endl;
    }
    
    ifstream file(bookName);
    
    // Error Check
    if(file.fail()){
        cout << "The file was not found. Kindly restart the program." << endl;
        exit(1);
    }
    
    // Logic
    book testBook = readData(file, userWord);
    printStatistics(testBook);
    
    if (encode) {
        ofstream outfile(encodedBookName);
        cout << encodedBookName << " has been written to the specified directory! Please store your encode key in a safe place to avoid losing data!" << endl << endl;
        encodeData(outfile, testBook, encodeKey);
    }
    
    // Close the file
    file.close();
    return 0;
}
