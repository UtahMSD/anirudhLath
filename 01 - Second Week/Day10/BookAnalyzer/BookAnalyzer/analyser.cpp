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
    
    // Command Line Arguments
    if(argc > 2) {
        bookName = argv[1];
        userWord = argv[2];
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
    
    //Logic
    book testBook = readData(file, userWord);
    printStatistics(testBook);
    
    return 0;
}
