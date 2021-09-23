//
//  main.cpp
//  mapAndSet
//
//  Created by Anirudh Lath on 9/22/21.
//

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <set>
#include <iterator>
#include <map>
#include <string>


using namespace std;

int main(int argc, const char * argv[]) {
    
    string filename = "1.txt";
    
    if( argc != 2 ){
        cout << "Error: no filename was entered. Program will now exit." << endl;
        exit(1);
    } else {
        filename = argv[1];
    }
    
    ifstream infile(filename);
    string word;
    set<string> uniqueWords;
    map<string, int> uniqueCount;
    
    if (infile.fail()) {
        cout << "File does not exist. Program will now exit.\n";
        exit(1);
    } else {
        cout << "The file was found, beginning analysis:\n";
    }
    
    while (infile >> word) {
        if (isalpha(word[0])) {
            uniqueWords.insert(word);
            uniqueCount[word]++;
        }
    }
    
    string popularWord;
    int popularCount = 0;
    
    for(auto &item: uniqueCount) {
        if(item.second > popularCount) {
            popularWord = item.first;
            popularCount = item.second;
        }
    }
    cout << "There are " << uniqueWords.size() << " unique words in this file:\n";
    cout << "The most popular word in the file is '" << popularWord << "' and it appeared " << popularCount << " times.\n";
    
    for(auto &item: uniqueCount) {
        cout << "The word '" << item.first << "' appeared " << item.second << " times.\n";
    }
    
    return 0;
}
