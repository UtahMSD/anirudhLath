//
//  helper.cpp
//  MakeYourOwnVector
//
//  Created by Anirudh Lath on 9/13/21.
//

#include "helper.hpp"
#include <iostream>
#include <stdlib.h>

myvector::myvector(){
    capacity = 10;
    size = 0;
    index = new int[10];
}

myvector::myvector( int initialCapacity ) {
    capacity = initialCapacity;
    size = 0;
    index = new int[initialCapacity];
}

int myvector::getSize() const {
    return size;
}

int* myvector::getAddress() const {
    return index;
}

int myvector::getCapacity() const {
    return capacity;
}

int myvector::getIndex(int i) const {
    return index[i];
}

void myvector::freeVector() {
    index = nullptr;
}

void myvector::pushBack(int num) {
    if (size < capacity) {
        index[size] = num;
    } else {
        growVector();
        index[size] = num;
    }
    
    size++;
}

void myvector::popBack() {
    if (size > 0) {
        size--;
        index[size] = NULL;
    } else {
        std::cout << "There are no elements in this vector to pop." << std::endl;
        exit(1);
    }
    

}

int myvector::get(int i) const {
    if (i >= size) {
        std::cout << "The index you have entered is out of range." << std::endl;
        exit(1);
    }
    return index[i];
}

void myvector::set(int i, int newValue) {
    if (i < size) {
        *(index + i) = newValue;
    } else {
        std::cout << "The index you have entered is out of range. Please try again with a valid index." << std::endl;
        exit(1);
    }
}

void myvector::growVector() {
    capacity *= 2;
    int * ind = new int[capacity];
    for(int i = 0; i < size; i++) {
        ind[i] = index[i];
    }
    index = nullptr;
    index = ind;
}
