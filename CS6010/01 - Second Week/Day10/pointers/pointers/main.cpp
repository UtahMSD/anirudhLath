//
//  main.cpp
//  pointers
//
//  Created by Anirudh Lath on 9/3/21.
//

#include <iostream>

using namespace std;

void swap(int* a, int* b) {
    int swap = *a;
    *a = *b;
    *b = swap;
}

void printArray( int* array, int size) {
    for(int i = 0; i < size; i++) {
       // cout << *(array + i) << endl;
        cout << array[i] << endl;
    }
}

int main(int argc, const char * argv[]) {
    int i = 1;
    int j= 2;
    
    swap(&i, &j);
    
    return 0;
}
