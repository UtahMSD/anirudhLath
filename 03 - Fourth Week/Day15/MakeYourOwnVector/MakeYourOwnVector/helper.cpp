//
//  helper.cpp
//  MakeYourOwnVector
//
//  Created by Anirudh Lath on 9/13/21.
//

#include "helper.hpp"
#include <iostream>
#include <stdlib.h>

vector makeVector( int initialCapacity ) {
    vector vector1;
    vector1.capacity = initialCapacity;
    vector1.size = 0;
    vector1.index = new int[initialCapacity];
    
    return vector1;
}

void freeVector(vector &MyVec) {
    //delete [] MyVec.index;
    MyVec.index = nullptr;
}

void pushBack(vector &myVec, int num) {
    if (myVec.size < myVec.capacity) {
        myVec.index[myVec.size] = num;
    } else {
        growVector(myVec);
        myVec.index[myVec.size] = num;
    }
    
    myVec.size++;
}

void popBack(vector &myVec) {
    if (myVec.size > 0) {
        myVec.size--;
        myVec.index[myVec.size] = NULL;
    } else {
        std::cout << "There are no elements in this vector to pop." << std::endl;
        exit(1);
    }
    

}

int get(vector myVec, int index) {
    if (index >= myVec.size) {
        std::cout << "The index you have entered is out of range." << std::endl;
        exit(1);
    }
    return myVec.index[index];
}

void set(vector &myVec, int index, int newValue) {
    if (index < myVec.size) {
        *(myVec.index + index) = newValue;
    } else {
        std::cout << "The index you have entered is out of range. Please try again with a valid index." << std::endl;
        exit(1);
    }
}

void growVector( vector &myVec ) {
    myVec.capacity *= 2;
    int * index = new int[myVec.capacity];
    for(int i = 0; i < myVec.size; i++) {
        index[i] = myVec.index[i];
    }
    myVec.index = nullptr;
    myVec.index = index;
}
