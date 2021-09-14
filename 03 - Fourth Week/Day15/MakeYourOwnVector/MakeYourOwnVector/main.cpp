//
//  main.cpp
//  MakeYourOwnVector
//
//  Created by Anirudh Lath on 9/13/21.
//
#include "helper.hpp"
#include <iostream>



int main(int argc, const char * argv[]) {
    
    // T1: Make Vector Test
    vector testVector = makeVector(4);
    vector testVector2 = makeVector(10);
    vector testVector3 = makeVector(129);
    
    if (testVector.capacity == 4 && testVector.size == 0
        && testVector2.capacity == 10 && testVector2.size == 0
        && testVector3.capacity == 129 && testVector3.size == 0)
    {
        std::cout << "T1: makeVector() passed!\n";
    } else {
        std::cout << "T1: makeVector() failed!!!\n";
        exit(1);
    }
    
    // T2: pushBack Test
    for(int i = 0; i < 150; i++) {
        pushBack(testVector, i);
        pushBack(testVector2, i);
        pushBack(testVector3, i);
        if (testVector.size != (i + 1) && testVector.index[i] != i
            && testVector2.size != i + 1 && testVector2.index[i] != i
            && testVector3.size != i + 1 && testVector3.index[i] != i) {
            std::cout << "T2: pushBack() failed!!!\n";
            exit(1);
        }
    }
    std::cout << "T2: pushBack() passed!\n";
    
    // T3: get Test
    for (int i = 0; i < 150; i++) {
        if (get(testVector, i) != i
            && get(testVector2, i) != i
            && get(testVector2, i) != i ) {
            std::cout << "T3: get() failed!!!\n";
            exit(1);
        }
    }
    std::cout << "T3: get() passed!\n";
    
    // T4: set Test
    for (int i = 150; i > 0; i--) {
        set(testVector, i - 1, 150 - i);
        set(testVector2, i - 1, 150 - i);
        set(testVector3, i - 1, 150 - i);
        if (   get(testVector, i - 1) != 150 - i
            && get(testVector2, i - 1) != 150 - i
            && get(testVector3, i - 1) != 150 - i) {
            std::cout << "T4: set() failed!!!\n";
            exit(1);
        }
    }
    std::cout << "T4: set() passed!\n";
    
    // T5: growVector Test
    int vec1 = testVector.capacity;
    int vec2 = testVector2.capacity;
    int vec3 = testVector3.capacity;
    growVector(testVector);
    growVector(testVector2);
    growVector(testVector3);
    
    if (   testVector.capacity != vec1 * 2
        && testVector2.capacity != vec2 * 2
        && testVector3.capacity != vec3 * 2) {
        std::cout << "T5: growVector() failed!!!\n";
        exit(1);
    }
    std::cout << "T5: growVector() passed!\n";

    // T6: pushBack Test
    for(int i = 0; i < 150; i++) {
        popBack(testVector);
        popBack(testVector2);
        popBack(testVector3);
        if (testVector.size != 150 - i - 1 && testVector.index[i] != 0
            && testVector2.size != 150 - i - 1 && testVector2.index[i] != 0
            && testVector3.size != 150 - i - 1 && testVector3.index[i] != 0) {
            std::cout << "T6: popBack() failed!!!\n";
            exit(1);
        }
    }
    std::cout << "T6: popBack() passed!\n";
    
    // T7: freeVector Test
    int *myvec1 = testVector.index;
    int *myvec2 = testVector2.index;
    int *myvec3 = testVector3.index;
    
    freeVector(testVector);
    freeVector(testVector2);
    freeVector(testVector3);
    
    if (   testVector.index == myvec1
        && testVector2.index == myvec2
        && testVector3.index == myvec3) {
        std::cout << "T7: freeVector() failed!!!\n";
        exit(1);
    }
    std::cout << "T7: freeVector() passed!\n\n";
    
    std::cout << "*** ALL TESTS PASSED! ***\n\n";
    
    return 0;
}
