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
        }
    }
    std::cout << "T3: get() passed!\n";
    
    // T4: set Test
    for (int i = 150; i > 0; i--) {
        set(testVector, i - 1, 150 - i);
        set(testVector, i - 1, 150 - i);
        set(testVector, i - 1, 150 - i);
    }

    // T: pushBack Test
    for(int i = 0; i < 150; i++) {
        popBack(testVector);
        popBack(testVector2);
        popBack(testVector3);
        if (testVector.size != 150 - i - 1 && testVector.index[i] != 0
            && testVector2.size != 150 - i - 1 && testVector2.index[i] != 0
            && testVector3.size != 150 - i - 1 && testVector3.index[i] != 0) {
            std::cout << "T: popBack() failed!!!\n";
            exit(1);
        }
    }
    std::cout << "T: popBack() passed!\n";
    
//    pushBack(testVector, 5);
//    pushBack(testVector, 4);
//    pushBack(testVector, 3);
//    pushBack(testVector, 2);
//    pushBack(testVector, 1);
    
    for (int i = 0; i < testVector.size; i++) {
        std::cout << testVector.index[i] << " ";
    }
    
    std::cout << "| Size: " << testVector.size << " | Capacity: " << testVector.capacity << " | Address: " << testVector.index << std::endl;
    
    popBack(testVector);
    
    for (int i = 0; i < testVector.size; i++) {
        std::cout << testVector.index[i] << " ";
    }
    
    std::cout << "| Size: " << testVector.size << " | Capacity: " << testVector.capacity << " | Address: " << testVector.index << std::endl;
    
//    freeVector(testVector);
//
//    for (int i = 0; i < testVector.size; i++) {
//        std::cout << testVector.index[i] << " ";
//    }
//
//    std::cout << "| Size: " << testVector.size << " | Capacity: " << testVector.capacity << " | Address: " << testVector.index << std::endl;
    
    
    std::cout << "get() at index 2: " << get(testVector, 3) << std::endl;
    set(testVector, 3, 6);
    std::cout << "set() at index 4: " << *(testVector.index + 4) << std::endl;
    
    for (int i = 0; i < testVector.size; i++) {
        std::cout << testVector.index[i] << " ";
    }
    
    return 0;
}
