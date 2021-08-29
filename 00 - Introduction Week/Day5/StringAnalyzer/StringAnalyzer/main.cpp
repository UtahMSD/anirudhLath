//
//  main.cpp
//  StringAnalyzer
//
//  Created by Anirudh Lath on 8/27/21.
//
#include <iostream>
using namespace std;

bool IsTerminator(char c) {
    return (c == '.' or c == '!' or c == '?');
}

bool IsPunctuation(char c) {
    return (c == '.' or c == '!' or c == '?' or c == ',');
}

bool IsVowel(char c) {
    return (c == 'a'
    or c == 'e'
    or c == 'i'
    or c == 'o'
    or c == 'u'
    or c == 'y'
    or c == 'A'
    or c == 'E'
    or c == 'I'
    or c == 'O'
    or c == 'U'
    or c == 'Y');
}

bool IsConsonant(char c) {
    return (!IsVowel(c) and !IsPunctuation(c) and c != ' ');
}

int NumWords(string str) {
    int wordCount = 0;
    for (int i = 0; i < str.size(); i++) {
        if (str[i] == ' '){
            wordCount++;
        }
    }
    return (wordCount + 1);
}

int NumSentences(string str) {
    int wordCount = 0;
    for (int i = 0; i < str.size(); i++) {
        if (IsTerminator(str[i])){
            wordCount++;
        }
    }
    return wordCount;
}

int NumVowels(string str) {
    int wordCount = 0;
    for (int i = 0; i < str.size(); i++) {
        if (IsVowel(str[i])){
            wordCount++;
        }
    }
    return wordCount;
}

int NumConsonants(string str) {
    int wordCount = 0;
    for (int i = 0; i < str.size(); i++) {
        if (IsConsonant(str[i])){
            wordCount++;
        }
    }
    return wordCount;
}

double AverageWordLength(string s) {
    int charCount = 0;
    
    int wordCount = NumWords(s);
    for (int i = 0; i < s.size(); i++) {
        if (!IsPunctuation(s[i])) {
            charCount++;
            if (s[i] == ' ') {
                charCount--;
            }
        }
    }
    double average = (charCount * 1.000 /wordCount * 1.000);
    return average;
}

double AverageVowelsPerWord(string s) {
    int charCount = 0;
    
    int wordCount = NumWords(s);
    for (int i = 0; i < s.size(); i++) {
        if (IsVowel(s[i])) {
            charCount++;
            }
    }
    double average = (charCount * 1.000 /wordCount * 1.000);
    return average;
}

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
