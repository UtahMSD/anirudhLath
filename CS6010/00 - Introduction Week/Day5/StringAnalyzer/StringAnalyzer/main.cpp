//
//  main.cpp
//  StringAnalyzer
//
//  Created by Anirudh Lath on 8/27/21.
//
#include <iostream>
#include "LetterHelpers.hpp"
#include "WordHelpers.hpp"
using namespace std;

int main(int argc, const char * argv[]) {
    // Variable
    string input = "";
    bool on = true;
        
    while (on) {
        // Input
        cout << "\nPlease keep typing and then press enter to end:\n";
        getline(cin, input);
        // Program end
        if (input == "done" or input == "Done") {
            on = false;
            cout << "\nGoodbye.\n";
        } else {
            // Output
            cout << "Analysis:" << endl;
            cout << " Number of words: " << NumWords(input) << endl;
            cout << " Number of sentences: " << NumSentences(input) << endl;
            cout << " Number of vowels: " << NumVowels(input) << endl;
            cout << " Number of consonants: " << NumConsonants(input) << endl;
            cout << " Reading level (average word length): " << AverageWordLength(input) << endl;
            cout << " Average vowels per word: " << AverageVowelsPerWord(input) << endl;
        }
    }
    return 0;
}
